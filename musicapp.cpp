#include "musicapp.h"
#include <formDialog.h>

using namespace std;

musicapp::musicapp(QWidget *parent)
    : QMainWindow(parent), dialog(new formDialog(this))
{
    ui.setupUi(this);
    connect(dialog, &formDialog::dataSubmitted, this, &musicapp::handleDialogData);
}

musicapp::~musicapp()
{}

void musicapp::handleDialogData(const Album & album)
{
    ui.testLabel->setText(QString::number(album.numberOfTracks));
}


void musicapp::openAlbumForm()
{
    dialog->show();
}