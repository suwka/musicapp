#include "Song.h"

Song::Song(string title, bool listened)
{
	this->songTitle = title;
	this->listened = listened;
}

string Song::getSongTitle() const
{
	return this->songTitle;
}

bool Song::getListened() const
{
	return this->listened;
}

void Song::setListened(bool listened) {
	this->listened = listened;
}

