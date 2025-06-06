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

    void displayHeader(const string& title);

    string getValidInput(const string& prompt);

    int getValidNumber(const string& prompt, int min, int max);

    void bubbleSort(LinkedList<Song>& list, const string& criteria);

    void displaySongs(const LinkedList<Song>& songs, const string& title, bool);

    void displayPlaylists(const LinkedList<Playlist>& playlists, const string& title, bool);


public:
};
