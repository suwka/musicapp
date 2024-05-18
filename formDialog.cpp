#include "formDialog.h"
#include "Album.h"

formDialog::formDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

formDialog::~formDialog()
{}

void formDialog::addAlbumToTable() {
	Album album(ui.spinBox->value());
	emit dataSubmitted(album);
	this->close();
}