#include "Album.h"

Album::Album(string title, string artist, vector<string> songs) {
	this->albumTitle = title;
	this->albumArtist = artist;
	this->songList = songs;
}
string Album::getAlbumTitle() const {
	return this->albumTitle;
}

string Album::getAlbumArtist() const{
	return this->albumArtist;
}

vector<string> Album::getSongList() const{
	return this->songList;
}




