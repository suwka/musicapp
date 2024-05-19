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
	vector<string> songs({ "pierwsza", "druga" });
	//Album album("tytul", "autor", ui.numberOfTitlesInput->value(), songs);
	//Album album((ui.albumTitleInput->text()).toStdString());
	Album album((ui.albumTitleInput->text()).toStdString(),(ui.albumArtistInsput->text()).toStdString(), ui.numberOfTitlesInput->value(), songs);
	emit dataSubmitted(album);
	this->close();
}

