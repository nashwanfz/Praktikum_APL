#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Genre {
    string name;
    vector<string> games;
};

int main() {
    int attempt = 0;
    const int max_attempt = 5;
    string Admin_User = "Nashwan";
    string Admin_Pass = "125";
    string Guest_User = "Guest";
    string Guest_Pass = "125";

    const int numGenres = 5;
    Genre genres[numGenres] = {
        {"FPS", {"Call Of Duty", "CS:GO", "Valorant"}},
        {"RPG", {"Elden Ring", "The Witcher", "Minecraft"}},
        {"Tower Defense", {"Bloons Tower Defense", "Kingdom Rush", "Plant vs Zombie"}},
        {"Racing", {"Formula 1", "Asphalt", "Forza"}},
        {"Horror", {"Dead By Daylight", "Pacify", "Phasmophobia"}}
    };

    while (attempt < max_attempt) {
        cout << "Silahkan login sebagai admin atau user" << endl;
        string User, Password;
        cout << "Masukkan Username anda : ";
        cin >> User;
        cout << "Masukkan Password anda : ";
        cin >> Password;

        if (User == Admin_User && Password == Admin_Pass) {
            cout << "Selamat Datang Admin" << endl;
            while (true) {
                cout << "==============================" << endl;
                cout << "1. Tampilkan Data" << endl;
                cout << "2. Tambahkan Data" << endl;
                cout << "3. Ubah Data" << endl;
                cout << "4. Hapus Data" << endl;
                cout << "5. Log Out" << endl;
                cout << "==============================" << endl;
                string Option;
                cout << "Apa pilihan anda (1/2/3/4/5): ";
                cin >> Option;
                cout << "==============================" << endl;

                switch (stoi(Option)) {
                    case 1:
                        for (int i = 0; i < numGenres; ++i) {
                            cout << genres[i].name << " : ";
                            for (int j = 0; j < genres[i].games.size(); ++j) {
                                cout << genres[i].games[j];
                                if (j != genres[i].games.size() - 1) {
                                    cout << ", ";
                                }
                            }
                            cout << endl;
                        }
                        break;
                    case 2: {
                        string category, new_game;
                        cout << "Kategori mana yang ingin anda tambahkan game? ";
                        cin >> category;
                        cout << "Apa nama game yang ingin anda tambahkan? ";
                        cin >> new_game;
                        for (int i = 0; i < numGenres; ++i) {
                            if (genres[i].name == category) {
                                genres[i].games.push_back(new_game);
                                break;
                            }
                        }
                        break;
                    }
                    case 3: {
                        string category, new_game;
                        int game_index;
                        cout << "Kategori mana yang ingin anda ubah? ";
                        cin >> category;
                        for (int i = 0; i < numGenres; ++i) {
                            if (genres[i].name == category) {
                                cout << "Pilih game yang ingin anda ubah:" << endl;
                                for (int j = 0; j < genres[i].games.size(); ++j) {
                                    cout << j << ". " << genres[i].games[j] << endl;
                                }
                                cout << "Indeks game yang ingin diubah: ";
                                cin >> game_index;
                                cout << "Apa nama game pengganti mu? ";
                                cin >> new_game;
                                if (game_index >= 0 && game_index < genres[i].games.size()) {
                                    genres[i].games[game_index] = new_game;
                                } else {
                                    cout << "Indeks game tidak valid." << endl;
                                }
                                break;
                            }
                        }
                        break;
                    }
                    case 4: {
                        string category;
                        int game_index;
                        cout << "Kategori mana yang ingin anda hapus game? ";
                        cin >> category;
                        for (int i = 0; i < numGenres; ++i) {
                            if (genres[i].name == category) {
                                cout << "Pilih game yang ingin anda hapus:" << endl;
                                for (int j = 0; j < genres[i].games.size(); ++j) {
                                    cout << j << ". " << genres[i].games[j] << endl;
                                }
                                cout << "Indeks game yang ingin dihapus: ";
                                cin >> game_index;
                                if (game_index >= 0 && game_index < genres[i].games.size()) {
                                    genres[i].games.erase(genres[i].games.begin() + game_index);
                                } else {
                                    cout << "Indeks game tidak valid." << endl;
                                }
                                break;
                            }
                        }
                        break;
                    }
                    case 5:
                        cout << "Anda Telah Log Out" << endl;
                        break;
                    default:
                        cout << "Pilihan tidak valid" << endl;
                        break;
                }

                if (Option == "5") {
                    break;
                }
            }
        } else if (User == Guest_User && Password == Guest_Pass) {
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
            string Pilihan;
            cout << "Apa anda ingin mencoba program sebagai admin? (y/n) : ";
            cin >> Pilihan;
            if (Pilihan == "y") {
                cout << endl;
            } else {
                cout << "Terima Kasih telah memakai Dictionary ini" << endl;
                break;
            }
        } else {
            cout << "Kredential akun anda tidak tepat" << endl << endl;
            attempt++;
        }
    }

    if (attempt >= max_attempt) {
        cout << "Anda telah melewati batas attempt" << endl;
    }

    return 0;
}
