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

void MusicPlayer::run() {
    while (true) {
        displayHeader("Music Player");

        cout << BOLD << YELLOW << "1.Register\n";
        cout << "2.Login (User)\n";
        cout << "3.Login (Admin)\n";
        cout << "4.Exit" << RESET << "\n\n";

        int choice = getValidNumber("Choose an option: ", 1, 4);

        switch (choice) {
        case 1: registerUser(); break;
        case 2: loginUser(); break;
        case 3: loginAdmin(); break;
        case 4: return;
        }
        cout << "\nPress Enter to continue..."; cin.get();
    }
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

void MusicPlayer::userMenu() {
    while (true) {
        displayHeader("User Menu - " + currentUser->getUsername());
        cout << BOLD << YELLOW;
        cout << left
            << "+----+--------------------------+----+-----------------------------+\n"
            << "| No | Option                   | No | Option                      |\n"
            << "+----+--------------------------+----+-----------------------------+\n";

        cout << "| 1  | View All Songs           | 9  | Search Playlists            |\n"
            << "| 2  | View Favorites           | 10 | View Singer Page            |\n"
            << "| 3  | View Saved Songs         | 11 | Logout                      |\n"
            << "| 4  | View Playlists           | .. |                             |\n"
            << "| 5  | Create Playlist          | .. |                             |\n"
            << "| 6  | Edit Playlist            | .. |                             |\n"
            << "| 7  | Delete Playlist          | .. |                             |\n"
            << "| 8  | Search Songs             | .. |                             |\n";

        cout << "+----+--------------------------+----+-----------------------------+\n"
            << RESET;

        int choice = getValidNumber("Choose an option: ", 1, 11);
        switch (choice) {
        case 1: viewAllSongs(); break;
        case 2: viewFavorites(); break;
        case 3: viewSavedSongs(); break;
        case 4: viewPlaylists(); break;
        case 5: createPlaylist(); break;
        case 6: editPlaylist(); break;
        case 7: deletePlaylist(); break;
        case 8: searchSongs(); break;
        case 9: searchPlaylists(); break;
        case 10: viewSingerPage(); break;
        case 11: return;
        }
        cout << "Press Enter to continue..."; cin.get();
    }
}

void MusicPlayer::adminMenu() {
    while (true) {
        displayHeader("Admin Menu");
        cout << BOLD << YELLOW;
        cout << left
            << "+----+------------------------------+----+-------------------------------------+\n"
            << "| No | Option                       | No | Option                              |\n"
            << "+----+------------------------------+----+-------------------------------------+\n";

        cout << "| 1  | Add Song                     | 9  | Delete Singer                       |\n"
            << "| 2  | Edit Song                    | 10 | View Users                          |\n"
            << "| 3  | Delete Song                  | 11 | Edit User                           |\n"
            << "| 4  | Create Playlist              | 12 | Delete User                         |\n"
            << "| 5  | Edit Playlist                | 13 | Add Song to Playlist                |\n"
            << "| 6  | Delete Playlist              | 14 | Add Playlist to Singer              |\n"
            << "| 7  | Create Singer Page           | 15 | Remove Playlist from Singer         |\n"
            << "| 8  | Edit Singer Page             | 16 | Logout                              |\n";

        cout << "+----+------------------------------+----+-------------------------------------+\n"
            << RESET;

        int choice = getValidNumber("Choose an option: ", 1, 16);
        switch (choice) {
        case 1: addSong(); break;
        case 2: editSong(); break;
        case 3: deleteSong(); break;
        case 4: createPlaylist(); break;
        case 5: editPlaylist(); break;
        case 6: deletePlaylist(); break;
        case 7: createSinger(); break;
        case 8: editSinger(); break;
        case 9: deleteSinger(); break;
        case 10: viewUsers(); break;
        case 11: editUser(); break;
        case 12: deleteUser(); break;
        case 13: addSongToPlaylist(); break;
        case 14: addPlaylistToSinger(); break;
        case 15: removePlaylistFromSinger(); break;
        case 16: return;
        }
        cout << "Press Enter to continue..."; cin.get();
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

void MusicPlayer::createSinger() {
    displayHeader("Create Singer");

    string name = getValidInput("Enter singer name: ");
    int albumCount = getValidNumber("Enter album count: ", 0, 50);

    allSingers.PushBack(Singer(name, albumCount));

    cout << GREEN << "Singer page created!" << RESET << '\n';
}

void MusicPlayer::editSinger() {
    displayHeader("Edit Singer");
    displaySingers();

    if (allSingers.IsEmpty()) return;

    int index = getValidNumber("Enter singer number to edit: ", 1, allSingers.GetSize());
    Singer& singer = allSingers[index - 1];

    singer.setName(getValidInput("Enter new singer name: "));
    singer.setAlbumCount(getValidNumber("Enter new album count: ", 0, 100));

    cout << GREEN << "Singer page updated!" << RESET << '\n';
}

void MusicPlayer::deleteSinger() {
    displayHeader("Delete Singer");
    displaySingers();

    if (allSingers.IsEmpty()) return;

    int index = getValidNumber("Enter singer number to delete: ", 1, allSingers.GetSize());
    Singer singer = allSingers[index - 1];

    if (singer.getSongCount() > 0) {
        cout << RED << "Cannot delete singer with existing songs!" << RESET << '\n';
        return;
    }

    allSingers.Remove(singer);
    cout << GREEN << "Singer deleted successfully!" << RESET << '\n';
}

void MusicPlayer::addPlaylistToSinger() {
    displayHeader("Add Playlist to Singer");
    displaySingers();

    if (allSingers.IsEmpty()) return;

    int singerIndex = getValidNumber("Enter singer number: ", 1, allSingers.GetSize());
    Singer& singer = allSingers[singerIndex - 1];

    displayPlaylists(allPlaylists, "Available Playlists");

    if (allPlaylists.IsEmpty()) return;

    int plIndex = getValidNumber("Enter playlist number: ", 1, allPlaylists.GetSize());

    Playlist playlist = allPlaylists[plIndex - 1];

    if (!singer.getPlaylists().Contains(playlist)) {
        singer.getPlaylists().PushBack(playlist);
        cout << GREEN << "Playlist added to singer!" << RESET << '\n';
    }
    else {
        cout << RED << "Playlist already added to this singer!" << RESET << '\n';
    }
}

void MusicPlayer::removePlaylistFromSinger() {
    displayHeader("Remove Playlist from Singer");
    displaySingers();

    if (allSingers.IsEmpty()) return;

    int singerIndex = getValidNumber("Enter singer number: ", 1, allSingers.GetSize());
    Singer& singer = allSingers[singerIndex - 1];

    displayPlaylists(singer.getPlaylists(), "Singer Playlists");

    if (singer.getPlaylists().IsEmpty()) return;

    int plIndex = getValidNumber("Enter playlist number to remove: ", 1, singer.getPlaylists().GetSize());

    singer.getPlaylists().Remove(singer.getPlaylists()[plIndex - 1]);

    cout << GREEN << "Playlist removed from singer!" << RESET << '\n';
}

void MusicPlayer::viewUsers() {
    displayHeader("All Users");
    if (users.IsEmpty()) {
        cout << RED << "No users available!" << RESET << '\n';
        return;
    }
    cout << BOLD << YELLOW;
    cout << left
        << "+-----+-------------------------+\n"
        << "| No. | Username                |\n"
        << "+-----+-------------------------+\n";
    cout << RESET;

    for (int i = 0; i < users.GetSize(); i++) {
        cout << left << YELLOW << BOLD
            << "| " << setw(3) << i + 1 << " "
            << "| " << setw(24) << users[i].getUsername()
            << "|" << RESET << '\n';
    }

    cout << BOLD << YELLOW
        << "+-----+-------------------------+\n"
        << RESET;
}

void MusicPlayer::editUser() {
    displayHeader("Edit User");
    viewUsers();

    if (users.IsEmpty()) return;

    int index = getValidNumber("Enter user number to edit: ", 1, users.GetSize());

    User& user = users[index - 1];

    user.setUsername(getValidInput("Enter new username: "));
    user.setPassword(getValidInput("Enter new password: "));

    cout << GREEN << "User updated successfully!" << RESET << '\n';
}

void MusicPlayer::deleteUser() {
    displayHeader("Delete User");
    viewUsers();

    if (users.IsEmpty()) return;

    int index = getValidNumber("Enter user number to delete: ", 1, users.GetSize());

    users.Remove(users[index - 1]);

    cout << GREEN << "User deleted successfully!" << RESET << '\n';
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

void MusicPlayer::viewFavorites() {
    displaySongs(currentUser->getFavorites(), "Favorites");

    if (currentUser->getFavorites().IsEmpty()) return;

    cout << "\n1. Delete Song\n2. Play Favorites\n3. Back" << '\n';

    int choice = getValidNumber("Choose an option: ", 1, 3);

    if (choice == 1) {
        int index = getValidNumber("Enter song number to delete: ", 1, currentUser->getFavorites().GetSize());

        currentUser->getFavorites().Remove(currentUser->getFavorites()[index - 1]);

        cout << GREEN << "Song removed from favorites!" << RESET << '\n';
    }
    else if (choice == 2) {
        playFavorites();
    }
}

void MusicPlayer::playFavorites() {
    displayHeader("Now Playing - Favorites");

    if (currentUser->getFavorites().IsEmpty()) {
        cout << RED << "No favorite songs available!" << RESET << '\n';
        return;
    }

    string sortChoice = getValidInput("Sort playlist before playing? (y/n): ");
    if (sortChoice == "y" || sortChoice == "Y") {
        string criteria = getValidInput("Sort by (name/singer/year/genre): ");
        if (criteria != "name" && criteria != "singer" && criteria != "year" && criteria != "genre") {
            cout << RED << "Invalid criteria! Skipping sort." << RESET << '\n';
        }
        else {
            bubbleSort(currentUser->getFavorites(), criteria);
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
        displayHeader("Now Playing - Favorites");
        Song currentSong = currentUser->getFavorites()[currentIndex];
        auto songs = currentUser->getFavorites();
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
                currentIndex = rand() % currentUser->getFavorites().GetSize();
            }
            else if (mode == "Repeat") {
            }
            else {
                currentIndex++;
                if (currentIndex >= currentUser->getFavorites().GetSize()) {
                    if (isLoop) currentIndex = 0;
                    else {
                        cout << RED << "End of favorites list!" << RESET << '\n';
                        return;
                    }
                }
            }
            break;
        }
        case 2: {
            if (mode == "Random") {
                currentIndex = rand() % currentUser->getFavorites().GetSize();
            }
            else if (mode == "Repeat") {
            }
            else {
                currentIndex--;
                if (currentIndex < 0) {
                    if (isLoop) currentIndex = currentUser->getFavorites().GetSize() - 1;
                    else {
                        cout << RED << "Start of favorites list!" << RESET << '\n';
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

void MusicPlayer::viewSavedSongs() {
    displaySongs(currentUser->getSavedSongs(), "Saved Songs");

    if (currentUser->getSavedSongs().IsEmpty()) return;

    cout << "\n1. Delete Song\n2. Play Saved Songs\n3. Back" << '\n';

    int choice = getValidNumber("Choose an option: ", 1, 3);

    if (choice == 1) {
        int index = getValidNumber("Enter song number to delete: ", 1, currentUser->getSavedSongs().GetSize());

        currentUser->getSavedSongs().Remove(currentUser->getSavedSongs()[index - 1]);
        cout << GREEN << "Song removed from saved songs!" << RESET << '\n';
    }
    else if (choice == 2) {
        playSavedSongs();
    }
}

void MusicPlayer::playSavedSongs() {
    displayHeader("Now Playing - Saved Songs");

    if (currentUser->getSavedSongs().IsEmpty()) {
        cout << RED << "No saved songs available!" << RESET << '\n';
        return;
    }

    string sortChoice = getValidInput("Sort playlist before playing? (y/n): ");
    if (sortChoice == "y" || sortChoice == "Y") {
        string criteria = getValidInput("Sort by (name/singer/year/genre): ");
        if (criteria != "name" && criteria != "singer" && criteria != "year" && criteria != "genre") {
            cout << RED << "Invalid criteria! Skipping sort." << RESET << '\n';
        }
        else {
            bubbleSort(currentUser->getSavedSongs(), criteria);
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
        displayHeader("Now Playing - Saved Songs");
        Song currentSong = currentUser->getSavedSongs()[currentIndex];

        auto songs = currentUser->getSavedSongs();
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
                currentIndex = rand() % currentUser->getSavedSongs().GetSize();
            }
            else if (mode == "Repeat") {
            }
            else {
                currentIndex++;
                if (currentIndex >= currentUser->getSavedSongs().GetSize()) {
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
                currentIndex = rand() % currentUser->getSavedSongs().GetSize();
            }
            else if (mode == "Repeat") {
            }
            else {
                currentIndex--;
                if (currentIndex < 0) {
                    if (isLoop) currentIndex = currentUser->getSavedSongs().GetSize() - 1;
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

void MusicPlayer::editFavorites() {
    displaySongs(currentUser->getFavorites(), "Edit Favorites");

    if (currentUser->getFavorites().IsEmpty()) return;

    int index = getValidNumber("Enter song number to edit: ", 1, currentUser->getFavorites().GetSize());

    Song& song = currentUser->getFavorites()[index - 1];

    song.setName(getValidInput("Enter new song name: "));
    song.setSinger(getValidInput("Enter new singer name: "));
    song.setYear(getValidNumber("Enter new year: ", 1900, 2025));
    song.setGenre(getValidInput("Enter new genre: "));

    cout << GREEN << "Favorite song updated!" << RESET << '\n';
}

void MusicPlayer::editSavedSongs() {
    displaySongs(currentUser->getSavedSongs(), "Edit Saved Songs");

    if (currentUser->getSavedSongs().IsEmpty()) return;

    int index = getValidNumber("Enter song number to edit: ", 1, currentUser->getSavedSongs().GetSize());

    Song& song = currentUser->getSavedSongs()[index - 1];

    song.setName(getValidInput("Enter new song name: "));
    song.setSinger(getValidInput("Enter new singer name: "));
    song.setYear(getValidNumber("Enter new year: ", 1900, 2025));
    song.setGenre(getValidInput("Enter new genre: "));

    cout << GREEN << "Saved song updated!" << RESET << '\n';
}

void MusicPlayer::viewPlaylists() {
    displayHeader("Playlists");

    cout << "Your Playlists:\n";

    displayPlaylists(currentUser->getPlaylists(), "Your Playlists", false);

    cout << "\nAll Playlists:\n";

    displayPlaylists(allPlaylists, "All Playlists", false);
}

void MusicPlayer::searchSongs() {
    displayHeader("Search Songs");

    string term = getValidInput("Enter search term: ");

    LinkedList<Song> results;

    for (int i = 0; i < allSongs.GetSize(); i++) {
        if (allSongs[i].getName().find(term) != string::npos ||
            allSongs[i].getSinger().find(term) != string::npos ||
            allSongs[i].getGenre().find(term) != string::npos) {
            results.PushBack(allSongs[i]);
        }
    }
    displaySongs(results, "Search Results");
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

void MusicPlayer::displaySingers() {
    if (allSingers.IsEmpty()) {
        cout << RED << "No singers available!" << RESET << '\n';
        return;
    }
    cout << BOLD << YELLOW;
    cout << "+-----+--------------------------+----------+--------+" << '\n';
    cout << "| No. | Singer Name              | Albums   | Songs  |" << '\n';
    cout << "+-----+--------------------------+----------+--------+" << '\n';

    for (int i = 0; i < allSingers.GetSize(); i++) {
        cout << left << "| " << setw(3) << i + 1 << " "
            << "| " << setw(25) << left << allSingers[i].getName()
            << "| " << setw(8) << left << allSingers[i].getAlbumCount()
            << " | " << setw(6) << left << allSingers[i].getSongCount()
            << " |" << '\n';
    }

    cout << "+-----+--------------------------+----------+--------+" << RESET << '\n';

}

void MusicPlayer::viewSingerPage() {
    displayHeader("Singer Page");
    displaySingers();

    if (allSingers.IsEmpty()) return;

    int index = getValidNumber("Enter singer number: ", 1, allSingers.GetSize());

    Singer& singer = allSingers[index - 1];

    displayHeader(singer.getName());
    cout << YELLOW << "Singer: " << singer.getName() << "\nAlbums: " << singer.getAlbumCount()
        << "\nSongs: " << singer.getSongCount() << "\n\nSongs List:" << RESET << '\n';

    displaySongs(singer.getSongs(), "Singer Songs", false);

    cout << "\nAssociated Playlists:\n";
    displayPlaylists(singer.getPlaylists(), "Singer Playlists", false);
}

void MusicPlayer::playPlaylist() {
    displayHeader("Play Playlist");

    int counter = 1;
    cout << MAGENTA << "Your Playlists:\n" << RESET;
    for (int i = 0; i < currentUser->getPlaylists().GetSize(); i++, counter++) {
        cout << YELLOW << counter << ". " << currentUser->getPlaylists()[i].getName()
            << " (" << currentUser->getPlaylists()[i].getSongs().GetSize() << " songs)" << RESET << '\n';
    }

    cout << '\n' << MAGENTA << "All Playlists:\n" << RESET;
    for (int i = 0; i < allPlaylists.GetSize(); i++, counter++) {
        cout << YELLOW << counter << ". " << allPlaylists[i].getName()
            << " (" << allPlaylists[i].getSongs().GetSize() << " songs)" << RESET << '\n';
    }

    int totalPlaylists = currentUser->getPlaylists().GetSize() + allPlaylists.GetSize();
    int selection = getValidNumber("Enter playlist number: ", 1, totalPlaylists);

    Playlist* playlist = nullptr;
    if (selection <= currentUser->getPlaylists().GetSize()) {
        playlist = &currentUser->getPlaylists()[selection - 1];
    }
    else {
        int idx = selection - currentUser->getPlaylists().GetSize() - 1;
        playlist = &allPlaylists[idx];
    }

    if (!playlist || playlist->getSongs().IsEmpty()) {
        cout << RED << "Playlist not found or empty!" << RESET << '\n';
        return;
    }

    string sortChoice = getValidInput("Sort playlist before playing? (y/n): ");
    if (sortChoice == "y" || sortChoice == "Y") {
        string criteria = getValidInput("Sort by (name/singer/year/genre): ");
        if (criteria != "name" && criteria != "singer" && criteria != "year" && criteria != "genre") {
            cout << RED << "Invalid criteria! Skipping sort." << RESET << '\n';
        }
        else {
            bubbleSort(playlist->getSongs(), criteria);
            cout << GREEN << "Playlist sorted!" << RESET << '\n';
            displaySongs(playlist->getSongs(), "Sorted Playlist");
        }
    }

    string mode = getValidInput("Set play mode (Sequential/Random/Repeat): ");
    if (mode != "Sequential" && mode != "Random" && mode != "Repeat") {
        cout << RED << "Invalid play mode! Using Sequential." << RESET << '\n';
        mode = "Sequential";
    }
    playlist->setPlayMode(mode);
    string loop = getValidInput("Enable loop? (y/n): ");
    playlist->setIsLoop(loop == "y" || loop == "Y");
    playlist->setCurrentIndex(0);

    while (true) {
        displayHeader("Now Playing - " + playlist->getName());
        Song currentSong = playlist->getSongs()[playlist->getCurrentIndex()];
        auto songs = playlist->getSongs();
        cout << BOLD << YELLOW;
        cout << left
            << "+-----+------------------------------+--------------------------+--------+--------------+\n"
            << "| No. | Song Name                    | Singer                   | Year   | Genre        |\n"
            << "+-----+------------------------------+--------------------------+--------+--------------+\n";
        cout << RESET;

        for (int i = 0; i < songs.GetSize(); i++) {
            cout << left << YELLOW
                << "| " << setw(3) << i + 1 << " "
                << "| " << setw(28) << songs[i].getName()
                << "| " << setw(24) << songs[i].getSinger()
                << "| " << setw(6) << songs[i].getYear()
                << "| " << setw(16) << songs[i].getGenre()
                << "|" << DIM << BLINK << (i == playlist->getCurrentIndex() ? " <- Now Playing" : "") << RESET << '\n';
        }

        cout << BOLD << YELLOW
            << "+-----+------------------------------+--------------------------+--------+--------------+\n"
            << RESET;


        cout << "\n";
        cout << CYAN << BLINK;
        cout << "+--------------------------------------------------+\n";
        cout << "|                     Now Playing                  |\n";
        cout << "+--------------------------------------------------+\n";
        cout << "| Song   : " << setw(40) << left << currentSong.getName() << "|\n";
        cout << "| Singer : " << setw(40) << left << currentSong.getSinger() << "|\n";
        cout << "| Mode   : " << setw(40) << left << playlist->getPlayMode() << "|\n";
        cout << "| Loop   : " << setw(40) << left << (playlist->getIsLoop() ? "On" : "Off") << "|\n";
        cout << "+--------------------------------------------------+\n" << RESET;

        cout << GREEN;
        cout << "\n1. Next\n";
        cout << "2. Previous\n";
        cout << "3. Play Song\n";
        cout << "4. Stop\n";
        cout << "----------------\n";
        cout << RESET;

        int choice = getValidNumber("\nChoose an option: ", 1, 4);

        switch (choice) {
        case 1: {
            if (playlist->getPlayMode() == "Random") {
                playlist->setCurrentIndex(rand() % playlist->getSongs().GetSize());
            }
            else if (playlist->getPlayMode() == "Repeat") {
            }
            else {
                playlist->setCurrentIndex(playlist->getCurrentIndex() + 1);
                if (playlist->getCurrentIndex() >= playlist->getSongs().GetSize()) {
                    if (playlist->getIsLoop()) playlist->setCurrentIndex(0);
                    else {
                        cout << RED << "End of playlist!" << RESET << '\n';
                        return;
                    }
                }
            }
            break;
        }
        case 2: {
            if (playlist->getPlayMode() == "Random") {
                playlist->setCurrentIndex(rand() % playlist->getSongs().GetSize());
            }
            else if (playlist->getPlayMode() == "Repeat") {
            }
            else {
                playlist->setCurrentIndex(playlist->getCurrentIndex() - 1);
                if (playlist->getCurrentIndex() < 0) {
                    if (playlist->getIsLoop()) playlist->setCurrentIndex(playlist->getSongs().GetSize() - 1);
                    else {
                        cout << RED << "Start of playlist!" << RESET << '\n';
                        playlist->setCurrentIndex(0);
                    }
                }
            }
            break;
        }
        case 3: {
            int songIndex = getValidNumber("Enter song number to play: ", 1, playlist->getSongs().GetSize());
            playlist->setCurrentIndex(songIndex - 1);
            cout << GREEN << "Now playing '" << playlist->getSongs()[songIndex - 1].getName() << "'!" << RESET << '\n';
            break;
        }
        case 4: return;
        }
    }
}

void MusicPlayer::playAllSongs() {

    displayHeader("Now Playing - All Songs");

    if (allSongs.IsEmpty()) {
        cout << RED << "No songs available!" << RESET << '\n';
        return;
    }
    auto songs = allSongs;
    string sortChoice = getValidInput("Sort playlist before playing? (y/n): ");
    if (sortChoice == "y" || sortChoice == "Y") {
        string criteria = getValidInput("Sort by (name/singer/year/genre): ");
        if (criteria != "name" && criteria != "singer" && criteria != "year" && criteria != "genre") {
            cout << RED << "Invalid criteria! Skipping sort." << RESET << '\n';
        }
        else {
            bubbleSort(songs, criteria);
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
        displayHeader("Now Playing - All Songs");
        Song currentSong = allSongs[currentIndex];
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

        cout << BOLD << YELLOW
            << "+-----+------------------------------+--------------------------+--------+--------------+\n"
            << RESET;
        cout << "\n";
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
                currentIndex = rand() % allSongs.GetSize();
            }
            else if (mode == "Repeat") {
            }
            else {
                currentIndex++;
                if (currentIndex >= allSongs.GetSize()) {
                    if (isLoop) currentIndex = 0;
                    else {
                        cout << RED << "End of song list!" << RESET << '\n';
                        return;
                    }
                }
            }
            break;
        }
        case 2: {
            if (mode == "Random") {
                currentIndex = rand() % allSongs.GetSize();
            }
            else if (mode == "Repeat") {

            }
            else {
                currentIndex--;
                if (currentIndex < 0) {
                    if (isLoop) currentIndex = allSongs.GetSize() - 1;
                    else {
                        cout << RED << "Start of song list!" << RESET << '\n';
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