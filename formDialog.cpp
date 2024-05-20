#include "formDialog.h"
#include "Album.h"
#include <QFileDialog>
#include <QStringListModel>
#include <QString>


formDialog::formDialog(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    connect(ui.importAlbumButton, &QPushButton::clicked, this, &formDialog::loadDataFromFile);
}

formDialog::~formDialog()
{}

void formDialog::addAlbumToTable() {
    vector<Song> songList;

    QString tekst = ui.textEdit->toPlainText();
    string tekstStd = tekst.toStdString();
    string slowo;

    for (char znak : tekstStd) {
        if (znak == '\n') {
            if (!slowo.empty()) {
                songList.push_back(Song(slowo, 0));
                slowo.clear();
            }
        }
        else {
            slowo += znak;
        }
    }
    if (!slowo.empty()) {
        songList.push_back(Song(slowo, 0));
    }

    Album album((ui.albumTitleInput->text()).toStdString(), (ui.albumArtistInsput->text()).toStdString(), songList);
    emit dataSubmitted(album);
    this->close();
}

void formDialog::loadDataFromFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Wybierz plik do wczytania"), "", tr("Pliki tekstowe (*.txt)"));
    if (filePath.isEmpty()) {
        qDebug() << "Anulowano wybór pliku.";
        return;
    }
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Nie mo¿na otworzyæ pliku.";
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        ui.textEdit->append(line);
    }
    file.close();
}


