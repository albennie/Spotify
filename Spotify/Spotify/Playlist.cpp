#include "Playlist.h"

Playlist::Playlist(string n)
    : name(n), currentIndex(-1), playMode("Sequential"), isLoop(false) {}

string Playlist::getName() const {
    return name;
}

LinkedList<Song>& Playlist::getSongs() {
    return songs;
}

int Playlist::getCurrentIndex() const {
    return currentIndex;
}

string Playlist::getPlayMode() const {
    return playMode;
}

bool Playlist::getIsLoop() const {
    return isLoop;
}

void Playlist::setName(const string& n) {
    name = n;
}

void Playlist::setCurrentIndex(int i) {
    currentIndex = i;
}

void Playlist::setPlayMode(const std::string& m) {
    playMode = m;
}

void Playlist::setIsLoop(bool l) {
    isLoop = l;
}

bool Playlist::operator==(const Playlist& other) const {
    return name == other.name;
}

bool Playlist::operator!=(const Playlist& other) const {
    return !(*this == other);
}
