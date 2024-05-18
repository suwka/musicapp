#include "formDialog.h"

formDialog::formDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

formDialog::~formDialog()
{}

void formDialog::addAlbumToTable() {
	this->close();
}