#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_musicapp.h"
#include "Album.h"
#include "formDialog.h"

class musicapp : public QMainWindow
{
    Q_OBJECT

public:
    musicapp(QWidget* parent = nullptr);
    ~musicapp();

private:
    Ui::musicappClass ui;
    formDialog* dialog;
    vector<Album> albumList;
    int currentIndex = 0;

private slots:
    void openAlbumForm();
    void handleDialogData(Album album);
    void displayAlbumInfo(int index);
    void updateAlbumProgressBar();
};

