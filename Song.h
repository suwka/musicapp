#pragma once
#include <string>

using namespace std;

class Song
{
	string songTitle;
	bool listened;

public:
	Song(string title, bool listened);
	string getSongTitle() const;
	bool getListened() const;
	void setListened(bool listened);
};

