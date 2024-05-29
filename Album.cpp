#include "Album.h"

Album::Album(string title, string artist, vector<Song> songs, int status) {
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

int Album::getAlbumStatus() const
{
	return this->albumStatus;
}

vector<Song>& Album::getSongList(){
	return this->songList;
}

const vector<Song>& Album::getSongList() const
{
	return this->songList;
}

void Album::setAlbumStatus(int status)
{
	this->albumStatus = status;
}


void Album::addSong(const Song& song) {
	songList.push_back(song);
}

Album::Album(const string& title, const string& artist)
	: albumTitle(title), albumArtist(artist) {
}




