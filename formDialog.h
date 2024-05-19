#pragma once

#include <QDialog>
#include "ui_formDialog.h"
#include "Album.h"


class formDialog : public QDialog
{
	Q_OBJECT

public:
	formDialog(QWidget *parent = nullptr);
	~formDialog();

signals:
	void dataSubmitted(const Album& album);

private:
	Ui::formDialogClass ui;
	QList<Album> listView;

private slots:
	void addAlbumToTable();
	void loadDataFromFile();
};
