#include "Album.h"

Album::Album(string title, string artist, vector<Song> songs) {
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

vector<Song> Album::getSongList() const{
	return this->songList;
}




