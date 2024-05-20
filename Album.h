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

public:
	Album(string title, string artist, vector<Song> songs);
	string getAlbumTitle() const;
	string getAlbumArtist() const;
	vector<Song> getSongList() const;

};

