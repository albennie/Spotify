#pragma once
#include "Account.h"
#include "Playlist.h"

class User : public Account {
private:
    LinkedList<Song> favorites, savedSongs;
    LinkedList<Playlist> playlists;
public:
    User(string u = "", string p = "");
    LinkedList<Song>& getFavorites();
    LinkedList<Song>& getSavedSongs();
    LinkedList<Playlist>& getPlaylists();
    bool operator==(const User& other) const;
    bool operator!=(const User& other) const;
};
