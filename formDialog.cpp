#include "formDialog.h"
#include "Album.h"
#include <QFileDialog>
#include <QStringListModel>
#include <QString>
#include <QMessageBox>


formDialog::formDialog(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    connect(ui.importAlbumButton, &QPushButton::clicked, this, &formDialog::loadDataFromFile);
}

formDialog::~formDialog()
{}

void getSongsFromText(string textEdit, vector<Song>& songList) {
    string songName;
    for (char znak : textEdit) {
        if (znak == '\n') {
            if (!songName.empty()) {
                songList.push_back(Song(songName, 0));
                songName.clear();
            }
        }
        else
            songName += znak;
    }
    if (!songName.empty())
        songList.push_back(Song(songName, 0));
}

void formDialog::fillInputs(const Album& album) {
    ui.albumArtistInput->setText(QString::fromStdString(album.getAlbumArtist()));
    ui.albumTitleInput->setText(QString::fromStdString(album.getAlbumTitle()));
    const vector<Song>& songList = album.getSongList();

    for (const Song& song : songList) {
        ui.textEdit->append(QString::fromStdString(song.getSongTitle()));
    }
}

void formDialog::addAlbumToTable() {
    QMessageBox msgBox;
    string albumTitle = ui.albumTitleInput->text().toStdString();
    string albumArtist = ui.albumArtistInput->text().toStdString();
    string textEdit = ui.textEdit->toPlainText().toStdString();
    vector<Song> songList;
    getSongsFromText(textEdit, songList);

    if (albumTitle.empty() || albumArtist.empty() || songList.empty()) {
        msgBox.setText("Nalezy wypelnic wszystkie pola.");
        msgBox.exec();
    }
    else {
        ui.albumTitleInput->clear();
        ui.albumArtistInput->clear();
        ui.textEdit->clear();

        Album album(albumTitle, albumArtist, songList);
        emit dataSubmitted(album);
        this->close();

        msgBox.setText("Poprawnie dodano album.");
        msgBox.exec();
    }

    
}

void formDialog::loadDataFromFile()
{
    QMessageBox msgBox;

    QString filePath = QFileDialog::getOpenFileName(this, tr("Wybierz plik do wczytania"), "", tr("Pliki tekstowe (*.txt)"));
    if (filePath.isEmpty()) {
        msgBox.setText("Anulowano wybor pliku.");
        msgBox.exec();
        return;
    }
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        msgBox.setText("Nie mo¿na otworzyæ pliku.");
        msgBox.exec();
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        ui.textEdit->append(line);
    }
    file.close();
}