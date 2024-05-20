#include "Song.h"

Song::Song(string title, bool listened)
{
	this->songTitle = title;
	this->listened = listened;
}

string Song::getSongTitle()
{
	return this->songTitle;
}

bool Song::getListened()
{
	return this->listened;
}

