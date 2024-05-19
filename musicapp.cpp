#include "musicapp.h"
#include <formDialog.h>
#include <QFileDialog>
#include <QStringListModel>

musicapp::musicapp(QWidget* parent)
    : QMainWindow(parent), dialog(new formDialog(this))
{
    ui.setupUi(this);
    connect(dialog, &formDialog::dataSubmitted, this, &musicapp::handleDialogData);
    connect(ui.importAlbumButton, &QPushButton::clicked, this, &musicapp::loadDataFromFile); // Poprawiono po³¹czenie sygna³u i slotu
}

musicapp::~musicapp()
{}

void musicapp::handleDialogData(const Album& album)
{
    ui.testLabel->setText(QString::number(album.numberOfTracks));
}

void musicapp::openAlbumForm()
{
    dialog->show();
}

void musicapp::loadDataFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QTextStream in(&file);
    QStringList dataList;
    while (!in.atEnd()) {
        QString line = in.readLine();
        dataList << line;
    }
    file.close();
    QStringListModel* model = new QStringListModel(dataList, this);
    ui.listView->setModel(model);
}
