#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Genre {
    string name;
    vector<string> games;
};

// Fungsi untuk melakukan login
string login() {
    int attempt = 0;
    const int max_attempt = 3;
    string Admin_User = "Nashwan";
    string Admin_Pass = "125";
    string Guest_User = "Guest";
    string Guest_Pass = "125";

    while (attempt < max_attempt) {
        string User, Password;
        cout << "Masukkan Username anda : ";
        cin >> User;
        cout << "Masukkan Password anda : ";
        cin >> Password;

        if (User == Admin_User && Password == Admin_Pass) {
            return "admin"; // Berhasil login sebagai admin
        } else if (User == Guest_User && Password == Guest_Pass) {
            return "guest"; // Berhasil login sebagai guest
        } else {
            cout << "Kredential akun anda tidak tepat" << endl << endl;
            attempt++;
        }
    }

    cout << "Anda telah melewati batas attempt" << endl;
    return "failed"; // Gagal login
}

// Prosedur untuk menampilkan daftar genre dan permainan dalam suatu genre
void displayGenres(const Genre genres[], int numGenres) {
    for (int i = 0; i < numGenres; ++i) {
        cout << genres[i].name << ": ";
        for (int j = 0; j < genres[i].games.size(); ++j) {
            cout << genres[i].games[j];
            if (j != genres[i].games.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

// Fungsi untuk mencari genre berdasarkan nama game
string findGenreByGame(const Genre genres[], int numGenres, const string& game_name) {
    for (int i = 0; i < numGenres; ++i) {
        for (const string& game : genres[i].games) {
            size_t found = game.find(game_name);
            if (found != string::npos) {
                return genres[i].name;
            }
        }
    }
    return ""; // Jika tidak ditemukan genre
}

// Fungsi rekursif untuk mencari genre dari nama game
void searchGenre(const Genre genres[], int numGenres) {
    string game_name;
    cout << "Masukkan nama game: ";
    cin >> game_name;
    string genre = findGenreByGame(genres, numGenres, game_name);
    if (!genre.empty()) {
        cout << "Game " << game_name << " terdapat dalam genre " << genre << endl;
    } else {
        cout << "Game tidak ditemukan dalam daftar." << endl;
    }

    char choice;
    cout << "Apakah Anda ingin mencari genre dari game lain? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        searchGenre(genres, numGenres); // Panggil fungsi rekursif
    }
}

int main() {
    string status = login();
    if (status == "failed") {
        return 1; // Keluar jika gagal login
    }

    int numGenres = 5; // Jumlah genre awal
    Genre genres[numGenres] = {
        {"FPS", {"Call Of Duty", "CS:GO", "Valorant"}},
        {"RPG", {"Elden Ring", "The Witcher", "Minecraft"}},
        {"Tower Defense", {"Bloons Tower Defense", "Kingdom Rush", "Plant vs Zombie"}},
        {"Racing", {"Formula 1", "Asphalt", "Forza"}},
        {"Horror", {"Dead By Daylight", "Pacify", "Phasmophobia"}}
    };

    while (true) {
        cout << "==============================" << endl;
        cout << "1. Tampilkan Data" << endl;
        if (status == "admin") {
            cout << "2. Tambahkan Data" << endl;
            cout << "3. Ubah Data" << endl;
            cout << "4. Hapus Data" << endl;
        }
        cout << "5. Cari Genre dari Nama Game" << endl;
        cout << "6. Log Out" << endl;
        cout << "==============================" << endl;
        string Option;
        cout << "Apa pilihan anda (1/2/3/4/5/6): ";
        cin >> Option;
        cout << "==============================" << endl;

        switch (stoi(Option)) {
            case 1:
                displayGenres(genres, numGenres);
                break;
            case 2:
                if (status == "admin") {
                    string genre_name;
                    cout << "Masukkan nama genre: ";
                    cin >> genre_name;

                    // Cari apakah genre sudah ada
                    bool genre_exists = false;
                    for (int i = 0; i < numGenres; ++i) {
                        if (genres[i].name == genre_name) {
                            genre_exists = true;
                            break;
                        }
                    }

                    if (genre_exists) {
                        string game_name;
                        cout << "Masukkan nama game yang ingin ditambahkan: ";
                        cin >> game_name;

                        // Tambahkan game ke genre yang sesuai
                        for (int i = 0; i < numGenres; ++i) {
                            if (genres[i].name == genre_name) {
                                genres[i].games.push_back(game_name);
                                cout << "Game berhasil ditambahkan ke genre " << genre_name << endl;
                                break;
                            }
                        }
                    } else {
                        cout << "Genre tidak ditemukan." << endl;
                    }
                } else {
                    cout << "Anda tidak memiliki akses untuk menambahkan data." << endl;
                }
                break;
            case 3:
                if (status == "admin") {
                    string genre_name;
                    cout << "Masukkan nama genre yang ingin diubah: ";
                    cin >> genre_name;

                    // Cari apakah genre sudah ada
                    bool genre_found = false;
                    for (int i = 0; i < numGenres; ++i) {
                        if (genres[i].name == genre_name) {
                            genre_found = true;

                            string game_name;
                            cout << "Masukkan nama game yang ingin diubah: ";
                            cin >> game_name;

                            // Cari apakah game ada dalam genre tersebut
                            bool game_found = false;
                            for (int j = 0; j < genres[i].games.size(); ++j) {
                                if (genres[i].games[j] == game_name) {
                                    game_found = true;

                                    string new_game_name;
                                    cout << "Masukkan nama baru game: ";
                                    cin >> new_game_name;

                                    // Ubah nama game
                                    genres[i].games[j] = new_game_name;
                                    cout << "Game berhasil diubah." << endl;
                                    break;
                                }
                            }

                            if (!game_found) {
                                cout << "Game tidak ditemukan dalam genre tersebut." << endl;
                            }

                            break;
                        }
                    }

                    if (!genre_found) {
                        cout << "Genre tidak ditemukan." << endl;
                    }
                } else {
                    cout << "Anda tidak memiliki akses untuk mengubah data." << endl;
                }
                break;
            case 4:
                if (status == "admin") {
                    string genre_name;
                    cout << "Masukkan nama genre yang ingin dihapus: ";
                    cin >> genre_name;

                    // Cari apakah genre sudah ada
                    bool genre_found = false;
                    for (int i = 0; i < numGenres; ++i) {
                        if (genres[i].name == genre_name) {
                            genre_found = true;

                            // Hapus genre dan game yang sesuai
                            for (int j = i; j < numGenres - 1; ++j) {
                                genres[j] = genres[j + 1];
                            }
                            numGenres--;

                            cout << "Genre dan game yang terkait berhasil dihapus." << endl;
                            break;
                        }
                    }

                    if (!genre_found) {
                        cout << "Genre tidak ditemukan." << endl;
                    }
                } else {
                    cout << "Anda tidak memiliki akses untuk menghapus data." << endl;
                }
                break;
            case 5:
                if (status == "guest" || status == "admin") {
                    searchGenre(genres, numGenres); // Panggil fungsi untuk mencari genre dari nama game
                } else {
                    cout << "Anda tidak memiliki akses untuk mencari genre." << endl;
                }
                break;
            case 6:
                if (status == "admin" || status == "guest") {
                    cout << "Anda Telah Log Out" << endl;
                    cout << "Apakah Anda ingin keluar dari program (y/n) atau login sebagai guest (g)? ";
                    char logout_choice;
                    cin >> logout_choice;
                    if (logout_choice == 'y' || logout_choice == 'Y') {
                        return 0; // Keluar dari program
                    } else if (logout_choice == 'g' || logout_choice == 'G') {
                        status = "guest"; // Set status menjadi guest
                        cout << "Anda Telah Log In sebagai Guest" << endl;
                    } else {
                        cout << "Pilihan tidak valid, Anda tetap masuk sebagai admin." << endl;
                    }
                }
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}
