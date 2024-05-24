#pragma once

#include <QtWidgets/QMainWindow>
#include <QStandardItemModel>
#include "ui_musicapp.h"
#include "Album.h"
#include "formDialog.h"

class musicapp : public QMainWindow
{
    Q_OBJECT

public:
    musicapp(QWidget* parent = nullptr);
    ~musicapp();

signals:
    void editAlbum(const Album& album);

private:
    Ui::musicappClass ui;
    formDialog* dialog;
    vector<Album> albumList;
    int currentIndex = 0;
    bool edit = 0;
    QStandardItemModel* model;


private slots:
    void openAlbumForm();
    void handleDialogData(Album album);
    void displayAlbumInfo(int index);
    void updateAlbumProgressBar();
    void openAlbumEdit();
    void exportAlbums();
    void importAlbums();
    void removeAlbum();

};

