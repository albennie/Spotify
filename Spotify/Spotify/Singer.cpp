#include "Singer.h"

Singer::Singer(string n, int ac) : name(n), albumCount(ac), songCount(0) {}

string Singer::getName() const {
    return name;
}

int Singer::getAlbumCount() const {
    return albumCount;
}

int Singer::getSongCount() const {
    return songCount;
}

LinkedList<Song>& Singer::getSongs() {
    return songs;
}

LinkedList<Playlist>& Singer::getPlaylists() {
    return playlists;
}

void Singer::setName(const std::string& n) {
    name = n;
}

void Singer::setAlbumCount(int ac) {
    albumCount = ac;
}

void Singer::incrementSongCount() {
    songCount++;
}

void Singer::decrementSongCount() {
    if (songCount > 0) songCount--;
}

bool Singer::operator==(const Singer& other) const {
    return name == other.name;
}

bool Singer::operator!=(const Singer& other) const {
    return !(*this == other);
}