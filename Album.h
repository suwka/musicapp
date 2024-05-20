#pragma once
#include <string>
#include <vector>
using namespace std;

class Album
{
	string albumTitle;
	string albumArtist;
	vector<string> songList;

public:
	Album(string title, string artist, vector<string> songs);
	string getAlbumTitle() const;
	string getAlbumArtist() const;
	vector<string> getSongList() const;

};

