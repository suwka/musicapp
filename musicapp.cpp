#include "musicapp.h"
#include <formDialog.h>
#include <QStringListModel>
#include <QStandardItem>
#include <Album.h>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

musicapp::musicapp(QWidget* parent)
    : QMainWindow(parent), dialog(new formDialog(this))
{
    ui.setupUi(this);

    connect(dialog, &formDialog::dataSubmitted, this, &musicapp::handleDialogData);
    connect(ui.albumListComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &musicapp::displayAlbumInfo);
    connect(ui.albumSongTable->model(), &QAbstractItemModel::dataChanged, this, &musicapp::updateAlbumProgressBar);
    connect(this, &musicapp::editAlbum, dialog, &formDialog::fillInputs);

    ui.albumSongTable->horizontalHeader()->setStretchLastSection(true);
    ui.albumSongTable->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);

    //export album button idk czy dziala
    connect(ui.exportAlbumButton, &QPushButton::clicked, this, &musicapp::exportAlbums);
    //import button
    connect(ui.importAlbumButton, &QPushButton::clicked, this, &musicapp::importAlbums);


}

musicapp::~musicapp()
{}

void musicapp::handleDialogData(Album album)
{
    if (edit == true) {
        albumList[currentIndex] = album;
        ui.albumListComboBox->setItemText(currentIndex, QString::fromStdString(album.getAlbumTitle()));
        displayAlbumInfo(currentIndex);
    }   
    else {
        albumList.push_back(album);
        ui.albumListComboBox->addItem(QString::fromStdString(album.getAlbumTitle()));
    }
    
}


void musicapp::openAlbumForm()
{
    edit = 0;
    dialog->show();
}

void musicapp::openAlbumEdit()
{
    if (albumList.empty()) {
        QMessageBox msgBox;
        msgBox.setText("Brak albumu do edycji.");
        msgBox.exec();
    }
    else {
        edit = 1;
        emit editAlbum(albumList[currentIndex]);
        dialog->show();
    }    
}

void musicapp::displayAlbumInfo(int index)
{
    currentIndex = index;
    if (index >= 0 && index < albumList.size()) {
        string albumArtist = albumList[index].getAlbumArtist();
        vector<Song> songList = albumList[index].getSongList();
        const int numberOfTracks = songList.size();
        const int albumStatus = albumList[index].getAlbumStatus();

        ui.albumArtistLabel->setText(QString::fromStdString(albumArtist));
        ui.numberOfSongsLabel->setText(QString::number(numberOfTracks));
        ui.albumProgressBar->setValue(albumStatus);

        QStandardItemModel* model = new QStandardItemModel(this);

        for (const Song& song : songList) {
            QStandardItem* item = new QStandardItem(QString::fromStdString(song.getSongTitle()));
            item->setCheckable(true);
            item->setCheckState(song.getListened() ? Qt::Checked : Qt::Unchecked);
            model->appendRow(item);
        }

        ui.albumSongTable->setModel(model);
        connect(model, &QStandardItemModel::dataChanged, this, &musicapp::updateAlbumProgressBar);
    }
}

void musicapp::updateAlbumProgressBar()
{
    int checkedCount = 0;
    int totalRows = ui.albumSongTable->model()->rowCount();
    vector<Song>& songList = albumList[currentIndex].getSongList();

    for (int row = 0; row < totalRows; ++row) {
        QModelIndex index = ui.albumSongTable->model()->index(row, 0);
        if (index.isValid()) {
            QVariant data = ui.albumSongTable->model()->data(index, Qt::CheckStateRole);
            if (data == Qt::Checked) {
                songList[row].setListened(1);
                ++checkedCount;
            }
            else
                songList[row].setListened(0);
        }
    }
    int progress = 0;
    if (totalRows > 0) {
        progress = (checkedCount * 100) / totalRows;
    }
    ui.albumProgressBar->setValue(progress);
    albumList[currentIndex].setAlbumStatus(ui.albumProgressBar->value());
}



void musicapp::exportAlbums()
{
    if (albumList.empty()) {
        QMessageBox::warning(this, "Blad eksportu", "Brak albumow do wyeksportowania.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Zapisz albumy", "", "JSON Files (*.json)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Blad otwarcia pliku", file.errorString());
        return;
    }

    QJsonArray albumsArray;
    for (const Album& album : albumList) {
        QJsonObject albumObject;
        albumObject["tytul"] = QString::fromStdString(album.getAlbumTitle());
        albumObject["artysta"] = QString::fromStdString(album.getAlbumArtist());

        QJsonArray songsArray;
        for (const Song& song : album.getSongList()) {
            QJsonObject songObject;
            songObject["nazwa"] = QString::fromStdString(song.getSongTitle());
            songObject["przesluchane"] = song.getListened() ? 1 : 0;
            songsArray.append(songObject);
        }

        albumObject["piosenki"] = songsArray;
        albumsArray.append(albumObject);
    }

    QJsonDocument doc(albumsArray);
    file.write(doc.toJson());
    file.close();

    QMessageBox::information(this, "Eksport zakonczony", "Albumy zostaly pomyslnie wyeksportowane");
}




void musicapp::importAlbums()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Importuj albumy", "", "Pliki JSON (*.json)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Blad", "Blad otwarcia pliku: " + file.errorString());
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isArray()) {
        QMessageBox::warning(this, "Blad", "Niepoprawny format JSON.");
        return;
    }

    QJsonArray albumsArray = doc.array();
    for (const QJsonValue& albumValue : albumsArray) {
        if (!albumValue.isObject()) {
            qDebug() << "Niepoprawny obiekt albumu w tablicy JSON.";
            continue;
        }

        QJsonObject albumObject = albumValue.toObject();
        QString title = albumObject["tytul"].toString();
        QString artist = albumObject["artysta"].toString();
        QJsonArray songsArray = albumObject["piosenki"].toArray();

        Album album(title.toStdString(), artist.toStdString());

        for (const QJsonValue& songValue : songsArray) {
            if (!songValue.isObject()) {
                qDebug() << "Niepoprawny obiekt piosenki w tablicy JSON.";
                continue;
            }

            QJsonObject songObject = songValue.toObject();
            QString songTitle = songObject["nazwa"].toString();
            bool listened = songObject["przesluchane"].toInt() == 1;

            Song song(songTitle.toStdString(), listened);
            album.getSongList().push_back(song);
        }

        albumList.push_back(album);
        ui.albumListComboBox->addItem(title);
    }

    QMessageBox::information(this, "Import zakonczony", "Albumy zostaly pomyslnie zaimportowane.");
}


