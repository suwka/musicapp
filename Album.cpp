#include "Album.h"
#include <QString>

Album::Album(int num) {
	this->numberOfTracks = num;
}
int Album::getNumberOfTracks() {
	return this->numberOfTracks;
}

