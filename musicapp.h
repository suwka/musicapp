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

private slots:
    void openAlbumForm();
    void handleDialogData(const Album& album);
    void displayAlbumInfo(int index);
    void updateAlbumProgressBar();
};

