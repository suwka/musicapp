#include "Album.h"
#include <QString>

Album::Album(string title, string artist, int num, vector<string> songs) {
	this->numberOfTracks = num;
	this->albumTitle = title;
	this->albumArtist = artist;
	this->songList = songs;
}
Album::Album(int num) {
	this->numberOfTracks = num;
}

Album::Album(string title) {
	this->albumTitle = title;
}

Album::Album(vector<string> songs) {
	this->songList = songs;
}

int Album::getNumberOfTracks() {
	return this->numberOfTracks;
}

string Album::getAlbumTitle() {
	return this->albumTitle;
}




