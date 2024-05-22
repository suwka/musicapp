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

	//ddo exportu :--)
	Album(const string& title, const string& artist);
	void addSong(const Song& song);

	string getAlbumTitle() const;
	string getAlbumArtist() const;
	int getAlbumStatus() const;
	vector<Song>& getSongList();
	const vector<Song>& getSongList() const;
	void setAlbumStatus(int status);

};

