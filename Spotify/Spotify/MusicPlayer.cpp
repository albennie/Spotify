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

void MusicPlayer::addSong() {
    displayHeader("Add Song");

    string name = getValidInput("Enter song name: ");
    string singer = getValidInput("Enter singer name: ");

    int year = getValidNumber("Enter year: ", 1900, 2025);

    string genre = getValidInput("Enter genre: ");
    Song song(name, singer, year, genre);

    allSongs.PushBack(song);

    for (int i = 0; i < allSingers.GetSize(); i++) {
        if (allSingers[i].getName() == singer) {
            allSingers[i].getSongs().PushBack(song);
            allSingers[i].incrementSongCount();
        }
    }
    cout << GREEN << "Song added successfully!" << RESET << '\n';
}

void MusicPlayer::editSong() {
    displayHeader("Edit Song");

    displaySongs(allSongs, "All Songs");

    if (allSongs.IsEmpty()) return;

    int index = getValidNumber("Enter song number to edit: ", 1, allSongs.GetSize());

    Song& song = allSongs[index - 1];
    string oldSinger = song.getSinger();

    song.setName(getValidInput("Enter new song name: "));
    song.setSinger(getValidInput("Enter new singer name: "));
    song.setYear(getValidNumber("Enter new year: ", 1900, 2025));
    song.setGenre(getValidInput("Enter new genre: "));

    if (oldSinger != song.getSinger()) {
        for (int i = 0; i < allSingers.GetSize(); i++) {
            if (allSingers[i].getName() == oldSinger) {
                allSingers[i].getSongs().Remove(song);
                allSingers[i].decrementSongCount();
            }
            if (allSingers[i].getName() == song.getSinger()) {
                allSingers[i].getSongs().PushBack(song);
                allSingers[i].incrementSongCount();
            }
        }
    }
    cout << GREEN << "Song updated successfully!" << RESET << '\n';
}

void MusicPlayer::deleteSong() {
    displayHeader("Delete Song");
    displaySongs(allSongs, "All Songs");

    if (allSongs.IsEmpty()) return;

    int index = getValidNumber("Enter song number to delete: ", 1, allSongs.GetSize());
    Song song = allSongs[index - 1];

    allSongs.Remove(song);
    for (int i = 0; i < allSingers.GetSize(); i++) {
        if (allSingers[i].getName() == song.getSinger()) {
            allSingers[i].getSongs().Remove(song);
            allSingers[i].decrementSongCount();
        }
    }

    for (int i = 0; i < allPlaylists.GetSize(); i++) {
        allPlaylists[i].getSongs().Remove(song);
    }

    for (int i = 0; i < users.GetSize(); i++) {
        for (int j = 0; j < users[i].getPlaylists().GetSize(); j++) {
            users[i].getPlaylists()[j].getSongs().Remove(song);
        }
        users[i].getFavorites().Remove(song);
        users[i].getSavedSongs().Remove(song);
    }

    cout << GREEN << "Song deleted successfully!" << RESET << '\n';
}

void MusicPlayer::viewAllSongs() {

    displaySongs(allSongs, "All Songs");
    if (allSongs.IsEmpty()) return;
    cout << BOLD << YELLOW;
    cout << "\n1. Add to Favorites\n2. Add to Saved Songs\n3. Add to Playlist\n4. Sort Songs\n5. Filter Songs\n6. Play All Songs\n7. Back" << '\n' << RESET;
    int choice = getValidNumber("Choose an option: ", 1, 7);
    switch (choice) {
    case 1:
    case 2:
    case 3: {
        int index = getValidNumber("Enter song number: ", 1, allSongs.GetSize());
        Song song = allSongs[index - 1];
        if (choice == 1) {
            if (!currentUser->getFavorites().Contains(song)) {
                currentUser->getFavorites().PushBack(song);
                cout << GREEN << "Added to favorites!" << RESET << '\n';
            }
            else {
                cout << RED << "Song already in favorites!" << RESET << '\n';
            }
        }
        else if (choice == 2) {
            if (!currentUser->getSavedSongs().Contains(song)) {
                currentUser->getSavedSongs().PushBack(song);
                cout << GREEN << "Added to saved songs!" << RESET << '\n';
            }
            else {
                cout << RED << "Song already in saved songs!" << RESET << '\n';
            }
        }
        else {
            string plName = getValidInput("Enter playlist name: ");
            for (int i = 0; i < currentUser->getPlaylists().GetSize(); i++) {
                if (currentUser->getPlaylists()[i].getName() == plName) {
                    currentUser->getPlaylists()[i].getSongs().PushBack(song);
                    cout << GREEN << "Song added to playlist!" << RESET << '\n';
                    return;
                }
            }
            cout << RED << "Playlist not found!" << RESET << '\n';
        }
        break;
    }
    case 4: {
        string criteria = getValidInput("Sort by (name/singer/year/genre): ");
        if (criteria != "name" && criteria != "singer" && criteria != "year" && criteria != "genre") {
            cout << RED << "Invalid criteria!" << RESET << '\n';
            return;
        }
        bubbleSort(allSongs, criteria);
        cout << GREEN << "Songs sorted!" << RESET << '\n';
        displaySongs(allSongs, "Sorted Songs");
        break;
    }
    case 5: filterSongs(allSongs, "All Songs"); break;
    case 6: playAllSongs(); break;
    case 7: break;
    }
}

void MusicPlayer::filterSongs(LinkedList<Song>& songs, const string& title) {
    displayHeader("Filter Songs - " + title);
    cout << GREEN << "Filter by:\n1. Singer\n2. Year\n3. Genre\n4. Back" << RESET << '\n';
    int choice = getValidNumber("Choose an option: ", 1, 4);
    if (choice == 4) return;

    LinkedList<Song> filteredSongs;
    string filterValue;
    int yearValue;

    switch (choice) {
    case 1:
        filterValue = getValidInput("Enter singer name: ");
        for (int i = 0; i < songs.GetSize(); i++) {
            if (songs[i].getSinger() == filterValue) {
                filteredSongs.PushBack(songs[i]);
            }
        }
        break;
    case 2:
        yearValue = getValidNumber("Enter year: ", 1900, 2025);
        for (int i = 0; i < songs.GetSize(); i++) {
            if (songs[i].getYear() == yearValue) {
                filteredSongs.PushBack(songs[i]);
            }
        }
        break;
    case 3:
        filterValue = getValidInput("Enter genre: ");
        for (int i = 0; i < songs.GetSize(); i++) {
            if (songs[i].getGenre() == filterValue) {
                filteredSongs.PushBack(songs[i]);
            }
        }
        break;
    }

    displaySongs(filteredSongs, "Filtered Songs");
    if (!filteredSongs.IsEmpty()) {
        cout << BOLD << YELLOW;
        cout << "\n1. Add to Favorites\n2. Add to Saved Songs\n3. Add to Playlist\n4. Play Songs\n5. Back" << RESET << '\n';
        int subChoice = getValidNumber("Choose an option: ", 1, 5);
        if (subChoice == 5) return;

        if (subChoice == 4)
        {
            displaySongs(filteredSongs, "Now Playing - Filtered Songs");

            string sortChoice = getValidInput("Sort playlist before playing? (y/n): ");
            if (sortChoice == "y" || sortChoice == "Y") {
                string criteria = getValidInput("Sort by (name/singer/year/genre): ");
                if (criteria != "name" && criteria != "singer" && criteria != "year" && criteria != "genre") {
                    cout << RED << "Invalid criteria! Skipping sort." << RESET << '\n';
                }
                else {
                    bubbleSort(filteredSongs, criteria);
                    cout << GREEN << "Playlist sorted!" << RESET << '\n';
                }
            }
            string mode = getValidInput("Set play mode (Sequential/Random/Repeat): ");
            if (mode != "Sequential" && mode != "Random" && mode != "Repeat") {
                cout << RED << "Invalid play mode! Using Sequential." << RESET << '\n';
                mode = "Sequential";
            }

            string loop = getValidInput("Enable loop? (y/n): ");
            bool isLoop = (loop == "y" || loop == "Y");
            int currentIndex = 0;

            while (true) {
                displayHeader("Now Playing - Filtered Songs");
                Song currentSong = filteredSongs[currentIndex];

                auto songs = filteredSongs;
                cout << BOLD << YELLOW;
                cout << left
                    << "+-----+------------------------------+--------------------------+--------+--------------+\n"
                    << "| No. | Song Name                    | Singer                   | Year   | Genre        |\n"
                    << "+-----+------------------------------+--------------------------+--------+--------------+\n";
                cout << RESET;

                for (int i = 0; i < songs.GetSize(); i++) {
                    cout << left << YELLOW
                        << "| " << setw(3) << i + 1 << " "
                        << "| " << setw(29) << songs[i].getName()
                        << "| " << setw(25) << songs[i].getSinger()
                        << "| " << setw(7) << songs[i].getYear()
                        << "| " << setw(13) << songs[i].getGenre()
                        << "|" << endl;
                }

                cout << YELLOW << BOLD
                    << "+-----+------------------------------+--------------------------+--------+--------------+\n"
                    << RESET;

                cout << CYAN << BLINK;
                cout << "+--------------------------------------------------+\n";
                cout << "|                     Now Playing                  |\n";
                cout << "+--------------------------------------------------+\n";
                cout << "| Song   : " << setw(40) << left << currentSong.getName() << "|\n";
                cout << "| Singer : " << setw(40) << left << currentSong.getSinger() << "|\n";
                cout << "| Mode   : " << setw(40) << left << mode << "|\n";
                cout << "| Loop   : " << setw(40) << left << (isLoop ? "On" : "Off") << "|\n";
                cout << "+--------------------------------------------------+\n\n" << RESET;

                cout << GREEN;
                cout << "1. Next\n";
                cout << "2. Previous\n";
                cout << "3. Stop\n";
                cout << "----------------\n";
                cout << RESET;

                int choice = getValidNumber("\nChoose an option: ", 1, 3);

                switch (choice) {
                case 1: {
                    if (mode == "Random") {
                        currentIndex = rand() % filteredSongs.GetSize();
                    }
                    else if (mode == "Repeat") {
                    }
                    else {
                        currentIndex++;
                        if (currentIndex >= filteredSongs.GetSize()) {
                            if (isLoop) currentIndex = 0;
                            else {
                                cout << RED << "End of saved songs list!" << RESET << '\n';
                                return;
                            }
                        }
                    }
                    break;
                }
                case 2: {
                    if (mode == "Random") {
                        currentIndex = rand() % filteredSongs.GetSize();
                    }
                    else if (mode == "Repeat") {
                    }
                    else {
                        currentIndex--;
                        if (currentIndex < 0) {
                            if (isLoop) currentIndex = filteredSongs.GetSize() - 1;
                            else {
                                cout << RED << "Start of saved songs list!" << RESET << '\n';
                                currentIndex = 0;
                            }
                        }
                    }
                    break;
                }
                case 3: return;
                }
            }
        }

        int index = getValidNumber("Enter song number: ", 1, filteredSongs.GetSize());
        Song song = filteredSongs[index - 1];
        if (subChoice == 1) {
            if (!currentUser->getFavorites().Contains(song)) {
                currentUser->getFavorites().PushBack(song);
                cout << GREEN << "Added to favorites!" << RESET << '\n';
            }
            else {
                cout << RED << "Song already in favorites!" << RESET << '\n';
            }
        }
        else if (subChoice == 2) {
            if (!currentUser->getSavedSongs().Contains(song)) {
                currentUser->getSavedSongs().PushBack(song);
                cout << GREEN << "Added to saved songs!" << RESET << '\n';
            }
            else {
                cout << RED << "Song already in saved songs!" << RESET << '\n';
            }
        }
        else if (subChoice == 3) {
            string plName = getValidInput("Enter playlist name: ");
            for (int i = 0; i < currentUser->getPlaylists().GetSize(); i++) {
                if (currentUser->getPlaylists()[i].getName() == plName) {
                    currentUser->getPlaylists()[i].getSongs().PushBack(song);
                    cout << GREEN << "Song added to playlist!" << RESET << '\n';
                    return;
                }
            }
            cout << RED << "Playlist not found!" << RESET << '\n';
        }
    }
}

void MusicPlayer::createPlaylist() {
    displayHeader("Create Playlist");
    string name = getValidInput("Enter playlist name: ");

    Playlist playlist(name);

    if (isAdminLoggedIn) allPlaylists.PushBack(playlist);
    else currentUser->getPlaylists().PushBack(playlist);

    cout << GREEN << "Playlist created successfully!" << RESET << '\n';
}

void MusicPlayer::editPlaylist() {
    displayHeader("Edit Playlist");

    LinkedList<Playlist>& playlists = isAdminLoggedIn ? allPlaylists : currentUser->getPlaylists();

    displayPlaylists(playlists, "Playlists");

    if (playlists.IsEmpty()) return;

    int index = getValidNumber("Enter playlist number to edit: ", 1, playlists.GetSize());
    Playlist& playlist = playlists[index - 1];

    while (true) {
        displayHeader("Edit Playlist - " + playlist.getName());

        cout << GREEN << "1. Change Playlist Name\n2. Delete Song from Playlist\n3. Back" << RESET << '\n';

        int choice = getValidNumber("Choose an option: ", 1, 3);

        if (choice == 1)
        {
            playlist.setName(getValidInput("Enter new playlist name: "));
            cout << GREEN << "Playlist name updated successfully!" << RESET << '\n';
        }
        else if (choice == 2)
        {
            displaySongs(playlist.getSongs(), "Playlist Songs");
            if (playlist.getSongs().IsEmpty()) break;
            int songIndex = getValidNumber("Enter song number to delete: ", 1, playlist.getSongs().GetSize());
            playlist.getSongs().Remove(playlist.getSongs()[songIndex - 1]);
            cout << GREEN << "Song removed from playlist!" << RESET << '\n';
        }
        else if (choice == 3)
        {
            return;
        }
        cout << "Press Enter to continue..."; cin.get();
    }
}

void MusicPlayer::deletePlaylist() {
    displayHeader("Delete Playlist");

    LinkedList<Playlist>& playlists = isAdminLoggedIn ? allPlaylists : currentUser->getPlaylists();

    displayPlaylists(playlists, "Playlists");

    if (playlists.IsEmpty()) return;

    int index = getValidNumber("Enter playlist number to delete: ", 1, playlists.GetSize());

    Playlist playlist = playlists[index - 1];

    playlists.Remove(playlist);

    for (int i = 0; i < allSingers.GetSize(); i++) {
        allSingers[i].getPlaylists().Remove(playlist);
    }
    cout << GREEN << "Playlist deleted successfully!" << RESET << '\n';
}

void MusicPlayer::addSongToPlaylist() {
    displayHeader("Add Song to Playlist");
    displaySongs(allSongs, "All Songs");

    if (allSongs.IsEmpty()) return;

    int songIndex = getValidNumber("Enter song number to add: ", 1, allSongs.GetSize());
    Song song = allSongs[songIndex - 1];

    LinkedList<Playlist>& playlists = isAdminLoggedIn ? allPlaylists : currentUser->getPlaylists();

    displayPlaylists(playlists, "Available Playlists");

    if (playlists.IsEmpty()) return;
    int plIndex = getValidNumber("Enter playlist number: ", 1, playlists.GetSize());
    Playlist& playlist = playlists[plIndex - 1];

    if (!playlist.getSongs().Contains(song)) {
        playlist.getSongs().PushBack(song);
        cout << GREEN << "Song added to playlist successfully!" << RESET << '\n';
    }
    else {
        cout << RED << "Song already exists in this playlist!" << RESET << '\n';
    }
}

void MusicPlayer::viewPlaylists() {
    displayHeader("Playlists");

    cout << "Your Playlists:\n";

    displayPlaylists(currentUser->getPlaylists(), "Your Playlists", false);

    cout << "\nAll Playlists:\n";

    displayPlaylists(allPlaylists, "All Playlists", false);
}

void MusicPlayer::searchPlaylists() {
    displayHeader("Search Playlists");

    string term = getValidInput("Enter search term: ");

    LinkedList<Playlist> results;

    for (int i = 0; i < allPlaylists.GetSize(); i++) {
        if (allPlaylists[i].getName().find(term) != string::npos) {
            results.PushBack(allPlaylists[i]);
        }
    }
    for (int i = 0; i < currentUser->getPlaylists().GetSize(); i++) {
        if (currentUser->getPlaylists()[i].getName().find(term) != string::npos) {
            results.PushBack(currentUser->getPlaylists()[i]);
        }
    }

    displayPlaylists(results, "Search Results");
}

