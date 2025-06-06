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

    void initializeDefaultData();

public:
    MusicPlayer();

    void run();

    void registerUser();

    void loginUser();

    void loginAdmin();

    void userMenu();

    void adminMenu();

    void addSong();

    void editSong();

    void deleteSong();

    void createPlaylist();

    void editPlaylist();

    void deletePlaylist();

    void createSinger();

    void editSinger();

    void deleteSinger();

    void addPlaylistToSinger();

    void removePlaylistFromSinger();

    void viewUsers();

    void editUser();

    void deleteUser();

    void viewAllSongs();

    void filterSongs(LinkedList<Song>& songs, const string& title);

    void addSongToPlaylist();

    void viewFavorites();

    void viewSavedSongs();

    void editFavorites();

    void editSavedSongs();

    void viewPlaylists();

    void searchSongs();

    void searchPlaylists();

    void displaySingers();

    void viewSingerPage();

    void playPlaylist();

    void playAllSongs();

    void playFavorites();

    void playSavedSongs();
};


