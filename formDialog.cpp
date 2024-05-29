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

void formDialog::closeEvent(QCloseEvent* event)
{
    clearInputs();
}

void formDialog::clearInputs() {
    ui.albumArtistInput->clear();
    ui.albumTitleInput->clear();
    ui.textEdit->clear();
}

void formDialog::fillInputs(const Album& album) {
    edit = 1;
    ui.albumArtistInput->setText(QString::fromStdString(album.getAlbumArtist()));
    ui.albumTitleInput->setText(QString::fromStdString(album.getAlbumTitle()));
    const vector<Song>& songList = album.getSongList();

    for (const Song& song : songList) {
        ui.textEdit->append(QString::fromStdString(song.getSongTitle()));
    }
}

void formDialog::addAlbumToTable() {
    string albumTitle = ui.albumTitleInput->text().toStdString();
    string albumArtist = ui.albumArtistInput->text().toStdString();
    string textEdit = ui.textEdit->toPlainText().toStdString();
    vector<Song> songList;
    getSongsFromText(textEdit, songList);

    if (albumTitle.empty() || albumArtist.empty() || songList.empty()) {
        QMessageBox::warning(this, "Blad wczytywania", "Nalezy wypelnic wszystkie pola.");
    }
    else {
        ui.albumTitleInput->clear();
        ui.albumArtistInput->clear();
        ui.textEdit->clear();

        Album album(albumTitle, albumArtist, songList);
        emit dataSubmitted(album);
        this->close();

        if (edit == 0)
            QMessageBox::information(this, "Dodanie albumu", "Poprawnie dodano album.");
        else {
            QMessageBox::information(this, "Edycja albumu", "Poprawnie edytowano album.");
            edit = 0;
        }
    }
}

void formDialog::loadDataFromFile()
{
    QMessageBox msgBox;

    QString filePath = QFileDialog::getOpenFileName(this, tr("Wybierz plik do wczytania"), "", tr("Pliki tekstowe (*.txt)"));
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Blad pliku", "Anulowano wybor pliku.");
        return;
    }
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Blad pliku", "Nie mozna otworzyc pliku.");
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        ui.textEdit->append(line);
    }
    file.close();
}