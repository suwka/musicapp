#pragma once

#include <QDialog>
#include "ui_formDialog.h"

class formDialog : public QDialog
{
	Q_OBJECT

public:
	formDialog(QWidget *parent = nullptr);
	~formDialog();

private:
	Ui::formDialogClass ui;

	private slots:
	void addAlbumToTable();
};
