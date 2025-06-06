#pragma once
#include <string>
using namespace std;

class Song {
private:
    string name, singer, genre;
    int year;
public:
    Song(string n = "", string s = "", int y = 0, string g = "");
    string getName() const;
    string getSinger() const;
    int getYear() const;
    string getGenre() const;
    void setName(const string& n);
    void setSinger(const string& s);
    void setYear(int y);
    void setGenre(const std::string& g);
    bool operator==(const Song& other) const;
    bool operator!=(const Song& other) const;
};

