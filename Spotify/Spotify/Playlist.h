#pragma once
#include "LinkedList.h"
#include "Song.h"
using namespace std;

class Playlist {
private:
    string name;
    LinkedList<Song> songs;
    int currentIndex;
    string playMode;
    bool isLoop;
public:
    Playlist(string n = "");
    string getName() const;
    LinkedList<Song>& getSongs();
	void setSongs(const LinkedList<Song> s){
        songs = s;
	}
    int getCurrentIndex() const;
    string getPlayMode() const;
    bool getIsLoop() const;
    void setName(const string& n);
    void setCurrentIndex(int i);
    void setPlayMode(const std::string& m);
    void setIsLoop(bool l);
    bool operator==(const Playlist& other) const;
    bool operator!=(const Playlist& other) const;
};

