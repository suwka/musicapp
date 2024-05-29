#pragma once
#include <string>
#include <vector>
#include <Song.h>
using namespace std;

class Album
{
	string albumTitle;
	string albumArtist;
	vector<Song> songList;
	int albumStatus;

public:
	Album(string title, string artist, vector<Song> songs, int status = 0);

	//do eksportu
	Album(const string& title, const string& artist);
	void addSong(const Song& song);

	string getAlbumTitle() const;
	string getAlbumArtist() const;
	int getAlbumStatus() const;
	const vector<Song>& getSongList() const;
	vector<Song>& getSongList();
	void setAlbumStatus(int status);

};

