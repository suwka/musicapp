#include "musicapp.h"
#include <formDialog.h>

musicapp::musicapp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

musicapp::~musicapp()
{}

void musicapp::openAlbumForm()
{
    formDialog test;
    test.exec();
}