#pragma once
#include <string>
#include "Playlist.h"
using namespace std;

class Singer {
private:
    string name;
    int albumCount, songCount;
    LinkedList<Song> songs;
    LinkedList<Playlist> playlists;
public:
    Singer(string n = "", int ac = 0);
    string getName() const;
    int getAlbumCount() const;
    int getSongCount() const;
    LinkedList<Song>& getSongs();
    LinkedList<Playlist>& getPlaylists();
    void setName(const std::string& n);
    void setAlbumCount(int ac);
    void incrementSongCount();
    void decrementSongCount();
    bool operator==(const Singer& other) const;
    bool operator!=(const Singer& other) const;
};