#include "User.h"

User::User(string u, string p) : Account(u, p) {}

LinkedList<Song>& User::getFavorites() {
    return favorites;
}

LinkedList<Song>& User::getSavedSongs() {
    return savedSongs;
}

LinkedList<Playlist>& User::getPlaylists() {
    return playlists;
}

bool User::operator==(const User& other) const {
    return username == other.username;
}

bool User::operator!=(const User& other) const {
    return !(*this == other);
}
