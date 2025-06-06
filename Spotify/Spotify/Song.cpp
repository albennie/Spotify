#include "Song.h"

Song::Song(string n, string s, int y, string g)
    : name(n), singer(s), year(y), genre(g) {}

string Song::getName() const {
    return name;
}

string Song::getSinger() const {
    return singer;
}

int Song::getYear() const {
    return year;
}

string Song::getGenre() const {
    return genre;
}

void Song::setName(const string& n) {
    name = n;
}

void Song::setSinger(const string& s) {
    singer = s;
}

void Song::setYear(int y) {
    year = y;
}

void Song::setGenre(const std::string& g) {
    genre = g;
}

bool Song::operator==(const Song& other) const {
    return name == other.name && singer == other.singer;
}

bool Song::operator!=(const Song& other) const {
    return !(*this == other);
}
