#include "musicapp.h"
#include <formDialog.h>
#include <QStringListModel>
#include <QStandardItem>
#include <Album.h>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

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



