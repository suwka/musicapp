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
	string getAlbumTitle() const;
	string getAlbumArtist() const;
	int getAlbumStatus() const;
	vector<Song>& getSongList();
	void setAlbumStatus(int status);

};

