#include "musicapp.h"
#include <formDialog.h>
#include <QStringListModel>
#include <QStandardItem>


musicapp::musicapp(QWidget* parent)
    : QMainWindow(parent), dialog(new formDialog(this))
{
    ui.setupUi(this);
    connect(dialog, &formDialog::dataSubmitted, this, &musicapp::handleDialogData);
    connect(ui.albumListComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &musicapp::updateAlbumArtistLabel);
    connect(ui.albumSongTable->model(), &QAbstractItemModel::dataChanged, this, &musicapp::updateAlbumProgressBar);

}

musicapp::~musicapp()
{}

void musicapp::handleDialogData(const Album& album)
{
    albumList.push_back(album);
    ui.albumListComboBox->addItem(QString::fromStdString(album.albumTitle));
    //ui.testLabel->setText(QString::fromStdString(albumList[0].albumArtist));
    //ui.testLabel->setText(QString::fromStdString(album.albumTitle));
    ui.testLabel->setText(QString::fromStdString(album.songList[0]));
}


void musicapp::openAlbumForm()
{
    dialog->show();
}

void musicapp::updateAlbumArtistLabel(int index)
{
    if (index >= 0 && index < albumList.size()) {
        const std::string& albumArtist = albumList[index].albumArtist;
        const std::vector<std::string>& songList = albumList[index].songList;
        const int numberOfTracks = songList.size();

        ui.albumArtistLabel->setText(QString::fromStdString(albumArtist));
        ui.numberOfSongsLabel->setText(QString::number(numberOfTracks));

        QStandardItemModel* model = new QStandardItemModel(this);

        for (const std::string& song : songList) {
            QStandardItem* item = new QStandardItem(QString::fromStdString(song));
            item->setCheckable(true);
            item->setCheckState(Qt::Unchecked);
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
    for (int row = 0; row < totalRows; ++row) {
        QModelIndex index = ui.albumSongTable->model()->index(row, 0);
        if (index.isValid()) {
            QVariant data = ui.albumSongTable->model()->data(index, Qt::CheckStateRole);
            if (data == Qt::Checked) {
                ++checkedCount;
            }
        }
    }
    int progress = 0;
    if (totalRows > 0) {
        progress = (checkedCount * 100) / totalRows;
    }
    ui.albumProgressBar->setValue(progress);
}

