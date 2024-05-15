#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_musicapp.h"

class musicapp : public QMainWindow
{
    Q_OBJECT

public:
    musicapp(QWidget *parent = nullptr);
    ~musicapp();

private:
    Ui::musicappClass ui;
};
