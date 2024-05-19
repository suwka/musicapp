#pragma once
#include <string>
#include <vector>
using namespace std;

class Album
{
public:
	int numberOfTracks;
	string albumTitle;
	string albumArtist;
	vector<string> songList;
	

	Album(string title, string artist, int num, vector<string> songs);
	Album(int num);
	Album(string title);
	Album(vector<string> songs);
	int getNumberOfTracks();
	string getAlbumTitle();

};

