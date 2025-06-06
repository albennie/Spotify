#include "MusicPlayer.h"
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <iomanip>

#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define BLINK       "\033[5m"
#define REVERSE     "\033[7m"

#define RESET       "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"

void MusicPlayer::displayHeader(const string& title) {
    system("cls");

    const int width = 70;
    string border(width, '=');

    int padding = (width - title.length()) / 2;
    int extraSpace = (width - title.length()) % 2;

    string centeredTitle = string(padding, ' ') + title + string(padding + extraSpace, ' ');

    cout << BOLD << RED << border << RESET << '\n';
    cout << BOLD << REVERSE << GREEN << centeredTitle << RESET << '\n';
    cout << BOLD << RED << border << RESET << "\n\n";
}

string MusicPlayer::getValidInput(const string& prompt) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) cout << RED << "Input cannot be empty!" << RESET << '\n';
    } while (input.empty());
    return input;
}

int MusicPlayer::getValidNumber(const string& prompt, int min, int max) {
    int num;
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        try {
            num = stoi(input);
            if (num >= min && num <= max) break;
            cout << RED << "Please enter a number between " << min << " and " << max << "!" << RESET << '\n';
        }
        catch (...) {
            cout << RED << "Invalid number!" << RESET << '\n';
        }
    }
    return num;
}

void MusicPlayer::bubbleSort(LinkedList<Song>& list, const string& criteria) {
    for (int i = 0; i < list.GetSize() - 1; i++) {

        auto current = list.getHead();

        for (int j = 0; j < list.GetSize() - i - 1; j++) {
            auto next = current->getNext();
            bool swap = false;
            if (criteria == "name") swap = current->getData().getName() > next->getData().getName();

            else if (criteria == "singer") swap = current->getData().getSinger() > next->getData().getSinger();

            else if (criteria == "year") swap = current->getData().getYear() > next->getData().getYear();

            else if (criteria == "genre") swap = current->getData().getGenre() > next->getData().getGenre();

            if (swap) {
                Song temp = current->getData();
                current->getDataRef() = next->getData();
                next->getDataRef() = temp;
            }
            current = next;
        }
    }
}

void MusicPlayer::displaySongs(const LinkedList<Song>& songs, const string& title, bool x = true) {

    if (x) displayHeader(title);

    if (songs.IsEmpty()) {
        cout << RED << "No songs available!" << RESET << '\n';
        return;
    }

    cout << BOLD << YELLOW;
    cout << left
        << "+-----+------------------------------+--------------------------+--------+--------------+\n"
        << "| No. | Song Name                    | Singer                   | Year   | Genre        |\n"
        << "+-----+------------------------------+--------------------------+--------+--------------+\n";
    cout << RESET;

    for (int i = 0; i < songs.GetSize(); i++) {
        cout << left << YELLOW << BOLD
            << "| " << setw(3) << i + 1 << " "
            << "| " << setw(29) << songs[i].getName()
            << "| " << setw(25) << songs[i].getSinger()
            << "| " << setw(7) << songs[i].getYear()
            << "| " << setw(13) << songs[i].getGenre()
            << "|" << RESET << endl;
    }

    cout << YELLOW << BOLD
        << "+-----+------------------------------+--------------------------+--------+--------------+\n"
        << RESET;
}

void MusicPlayer::displayPlaylists(const LinkedList<Playlist>& playlists, const string& title, bool x = true) {

    if (x) displayHeader(title);

    if (playlists.IsEmpty()) {
        cout << RED << "No playlists available!" << RESET << '\n';
        return;
    }
    cout << CYAN;
    cout << left
        << "+-----+------------------------------+-------------+\n"
        << "| No. | Playlist Name                | # of Songs  |\n"
        << "+-----+------------------------------+-------------+\n";
    cout << RESET;

    for (int i = 0; i < playlists.GetSize(); i++) {
        cout << left << CYAN
            << "| " << setw(3) << i + 1 << " "
            << "| " << setw(29) << playlists[i].getName()
            << "| " << setw(12) << playlists[i].getSongs().GetSize()
            << "|" << RESET << '\n';
    }

    cout << CYAN
        << "+-----+------------------------------+-------------+\n"
        << RESET;
}

void MusicPlayer::registerUser() {

    displayHeader("Register");

    string username = getValidInput("Enter username: ");

    for (int i = 0; i < users.GetSize(); i++) {
        if (users[i].getUsername() == username) {
            cout << RED << "Username already exists!" << RESET << '\n';
            return;
        }
    }

    string password = getValidInput("Enter password: ");

    users.PushBack(User(username, password));

    cout << GREEN << "Registration successful!" << RESET << '\n';
}

void MusicPlayer::loginUser() {
    displayHeader("User Login");

    string username = getValidInput("Enter username: ");
    string password = getValidInput("Enter password: ");

    for (int i = 0; i < users.GetSize(); i++) {
        if (users[i].getUsername() == username && users[i].getPassword() == password) {
            currentUser = &users[i];
            userMenu();
            currentUser = nullptr;
            return;
        }
    }
    cout << RED << "Invalid credentials!" << RESET << '\n';
}

void MusicPlayer::loginAdmin() {
    displayHeader("Admin Login");

    string username = getValidInput("Enter username: ");
    string password = getValidInput("Enter password: ");

    if (admin.login(username, password)) {
        isAdminLoggedIn = true;
        adminMenu();
        isAdminLoggedIn = false;
    }
    else {
        cout << RED << "Invalid credentials!" << RESET << '\n';
    }
}

