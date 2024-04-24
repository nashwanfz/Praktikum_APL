#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Untuk fungsi sort dan find_if
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
void displayGenres(const vector<Genre>& genres) {
    for (const Genre& genre : genres) {
        cout << genre.name << ": ";
        for (size_t i = 0; i < genre.games.size(); ++i) {
            cout << genre.games[i];
            if (i != genre.games.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

// Fungsi untuk menambahkan game ke dalam genre
void addGameToGenre(vector<Genre>* genres_ptr, const string& genre_name, const string& game_name) {
    auto& genres = *genres_ptr; // Dereference pointer ke vector genres
    auto genre_it = find_if(genres.begin(), genres.end(), [&genre_name](const Genre& g) {
        return g.name == genre_name;
    });

    if (genre_it != genres.end()) {
        genre_it->games.push_back(game_name);
        cout << "Game berhasil ditambahkan ke genre " << genre_name << endl;
    } else {
        cout << "Genre tidak ditemukan." << endl;
    }
}

// Fungsi untuk mengubah nama game dalam suatu genre
void changeGameName(vector<Genre>* genres_ptr, const string& genre_name, const string& old_game_name, const string& new_game_name) {
    auto& genres = *genres_ptr; // Dereference pointer ke vector genres
    auto genre_it = find_if(genres.begin(), genres.end(), [&genre_name](const Genre& g) {
        return g.name == genre_name;
    });

    if (genre_it != genres.end()) {
        auto game_it = find(genre_it->games.begin(), genre_it->games.end(), old_game_name);
        if (game_it != genre_it->games.end()) {
            *game_it = new_game_name;
            cout << "Game berhasil diubah." << endl;
        } else {
            cout << "Game tidak ditemukan dalam genre tersebut." << endl;
        }
    } else {
        cout << "Genre tidak ditemukan." << endl;
    }
}

// Fungsi untuk menghapus genre dan game yang terkait
void deleteGenre(vector<Genre>* genres_ptr, const string& genre_name) {
    auto& genres = *genres_ptr; // Dereference pointer ke vector genres
    auto genre_it = find_if(genres.begin(), genres.end(), [&genre_name](const Genre& g) {
        return g.name == genre_name;
    });

    if (genre_it != genres.end()) {
        genres.erase(genre_it);
        cout << "Genre dan game yang terkait berhasil dihapus." << endl;
    } else {
        cout << "Genre tidak ditemukan." << endl;
    }
}

// Fungsi untuk sorting berdasarkan abjad nama genre
void sortGenresByName(vector<Genre>& genres) {
    sort(genres.begin(), genres.end(), [](const Genre& a, const Genre& b) {
        return a.name < b.name;
    });
}

// Fungsi untuk mencari genre berdasarkan kriteria
void searchGenreByCriteria(vector<Genre>& genres) {
    cout << "Pilih kriteria pencarian: " << endl;
    cout << "1. Berdasarkan jumlah game terbanyak hingga terkedikit" << endl;
    cout << "2. Berdasarkan jumlah game terkecil hingga terbanyak" << endl;
    cout << "3. Berdasarkan urutan abjad nama genre" << endl;
    cout << "Masukkan pilihan anda (1/2/3): ";
    int searchOption;
    cin >> searchOption;
    cout << "==============================" << endl;
    switch (searchOption) {
        case 1:
            sort(genres.begin(), genres.end(), [](const Genre& a, const Genre& b) {
                return a.games.size() > b.games.size();
            });
            cout << "Hasil pengurutan berdasarkan jumlah game terbanyak hingga terkedikit:" << endl;
            break;
        case 2:
            sort(genres.begin(), genres.end(), [](const Genre& a, const Genre& b) {
                return a.games.size() < b.games.size();
            });
            cout << "Hasil pengurutan berdasarkan jumlah game terkecil hingga terbanyak:" << endl;
            break;
        case 3:
            sortGenresByName(genres);
            cout << "Hasil pengurutan berdasarkan urutan abjad nama genre:" << endl;
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
            return;
    }
    for (const auto& genre : genres) {
        cout << genre.name << endl;
    }
}

int main() {
    string status = login();
    if (status == "failed") {
        return 1; // Keluar jika gagal login
    }

    vector<Genre> genres = {
        {"FPS", {"Call Of Duty", "CS:GO", "Valorant"}},
        {"RPG", {"Elden Ring", "The Witcher", "Minecraft"}},
        {"Tower Defense", {"Bloons Tower Defense", "Kingdom Rush", "Plant vs Zombie"}},
        {"Racing", {"Formula 1", "Asphalt", "Forza"}},
        {"Horror", {"Dead By Daylight", "Pacify", "Phasmophobia"}}
    };

    while (true) {
        cout << "==============================" << endl;
        cout << "1. Tampilkan Data" << endl;
        cout << "2. Tampilkan Data (Sort Ascending)" << endl;
        cout << "3. Tampilkan Data (Sort Decending)" << endl;
        cout << "4. Tampilkan Data (Sort Ascending Abjad awal Genre)" << endl;
        cout << "5. Cari Genre Berdasarkan Kriteria" << endl;
        cout << "6. Cari Game dalam Genre" << endl;
        cout << "7. Tambahkan Data" << endl;
        cout << "8. Ubah Data" << endl;
        cout << "9. Hapus Data" << endl;
        cout << "10. Log Out" << endl;
        cout << "==============================" << endl;
        string Option;
        cout << "Apa pilihan anda (1/2/3/4/5/6/7/8/9): ";
        cin >> Option;
        cout << "==============================" << endl;

        switch (stoi(Option)) {
            case 1:
                displayGenres(genres);
                break;
            case 2:
                sortGenresByName(genres);
                displayGenres(genres);
                break;
            case 3:
                sortGenresByName(genres);
                reverse(genres.begin(), genres.end());
                displayGenres(genres);
                break;
            case 4:
                sortGenresByName(genres);
                displayGenres(genres);
                break;
            case 5:
                searchGenreByCriteria(genres);
                break;
            case 6:
                cout << "Fitur ini belum tersedia. (Sudah tidak sanggup untuk menambahkan Fungsi Search Ke4 :) )" << endl;
                break;
            case 7:
                if (status == "admin") {
                    string genre_name, game_name;
                    cout << "Masukkan nama genre: ";
                    cin >> genre_name;
                    cout << "Masukkan nama game yang ingin ditambahkan: ";
                    cin >> game_name;
                    addGameToGenre(&genres, genre_name, game_name); // Menggunakan pointer ke vector genres
                } else {
                    cout << "Anda tidak memiliki akses untuk menambahkan data." << endl;
                }
                break;
            case 8:
                if (status == "admin") {
                    string genre_name, old_game_name, new_game_name;
                    cout << "Masukkan nama genre yang ingin diubah: ";
                    cin >> genre_name;
                    cout << "Masukkan nama game yang ingin diubah: ";
                    cin >> old_game_name;
                    cout << "Masukkan nama baru game: ";
                    cin >> new_game_name;
                    changeGameName(&genres, genre_name, old_game_name, new_game_name); // Menggunakan pointer ke vector genres
                } else {
                    cout << "Anda tidak memiliki akses untuk mengubah data." << endl;
                }
                break;
            case 9:
                if (status == "admin") {
                    string genre_name;
                    cout << "Masukkan nama genre yang ingin dihapus: ";
                    cin >> genre_name;
                    deleteGenre(&genres, genre_name); // Menggunakan pointer ke vector genres
                } else {
                    cout << "Anda tidak memiliki akses untuk menghapus data." << endl;
                }
                break;
            case 10:
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
