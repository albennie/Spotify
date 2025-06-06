#pragma once
#include "Admin.h"
#include "Singer.h"
#include "User.h"

class MusicPlayer {
private:
    LinkedList<Song> allSongs;
    LinkedList<Playlist> allPlaylists;
    LinkedList<Singer> allSingers;
    LinkedList<User> users;
    Admin admin;
    User* currentUser = nullptr;
    bool isAdminLoggedIn = false;
public:
};
