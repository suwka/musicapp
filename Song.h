#pragma once
#include <string>

using namespace std;

class Song
{
	string songTitle;
	bool listened;

public:
	Song(string title, bool listened = 0);
	string getSongTitle();
	bool getListened();
};

