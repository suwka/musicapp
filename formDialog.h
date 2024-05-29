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

public slots:
	void fillInputs(const Album& album);

protected:
	void closeEvent(QCloseEvent* event) override;

private:
	Ui::formDialogClass ui;
	bool edit = 0;
	void clearInputs();

private slots:
	void addAlbumToTable();
	void loadDataFromFile();
};
