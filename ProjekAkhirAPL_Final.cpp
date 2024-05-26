#include <iostream>
#include <string> 
#include <conio.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;
const int maxdata = 100;
struct Akun {
    string username;
    int password;
    string role;
};

const int maxAkun = 100;
Akun akun[maxAkun] = {{"Bosbesar", 123, "admin"}};
int jumlah_akun = 1;


struct Management
{
    string Karyawan[maxdata];
    int ID_Karyawan[maxdata];
    string* Tugas; // Mengubah Tugas menjadi array dinamis
    bool absen[maxdata];
    bool status_absensi[maxdata];
    bool status_tugas[maxdata];
    Management(){
        Tugas = new string[maxdata]; // Mengalokasikan memori untuk Tugas
        for (int i = 0; i < maxdata; i++)
        {
             Karyawan[i] = "";
            ID_Karyawan[i] = 0;
            Tugas[i] = ""; // Inisialisasi tugas menjadi string kosong
            status_tugas[i] = false;
        }   
    }
    ~Management() {
        delete[] Tugas; // Membebaskan memori saat objek dihancurkan
    }
};

Management management;
int jumlah_karyawan = 0;

void muat_data_karyawan(Management& management) {
    ifstream file("Karyawan.txt");
    string nama_karyawan;
    int id_karyawan;
    int i = 0;

    if (file.is_open()) {
        while (file >> id_karyawan) {
            getline(file, nama_karyawan, ',');
            getline(file, nama_karyawan); // Membaca sisa baris (nama karyawan)

            management.ID_Karyawan[i] = id_karyawan;
            management.Karyawan[i] = nama_karyawan;
            management.absen[i] = false; // Inisialisasi status absen
            management.status_absensi[i] = false; // Inisialisasi status absensi
            i++;
        }
        file.close();
    } else {
        cout << "Tidak bisa membuka file Karyawan.txt untuk memuat data." << endl;
    }
}

void sorting(Management* management) {
    for (int i = 0; i < maxdata - 1; ++i) {
        for (int j = i + 1; j < maxdata; ++j) {
            if (management->ID_Karyawan[i] > management->ID_Karyawan[j]) {
                // Tukar elemen
                swap(management->Karyawan[i], management->Karyawan[j]);
                swap(management->ID_Karyawan[i], management->ID_Karyawan[j]);
                swap(management->Tugas[i], management->Tugas[j]);
                swap(management->absen[i], management->absen[j]);
                swap(management->status_absensi[i], management->status_absensi[j]);
                swap(management->status_tugas[i], management->status_tugas[j]);
            }
        }
    }
}

void search(Management* management) {
    int id_karyawan;
    bool karyawan_ditemukan = false;

    cout << "Masukkan ID Karyawan yang ingin dicari: ";
    cin >> id_karyawan;

    // Cari karyawan dengan ID yang sesuai
    for (int i = 0; i < maxdata; ++i) {
        if (management->ID_Karyawan[i] == id_karyawan) {
            cout << "Karyawan Ditemukan:" << endl;
            cout << "Nama: " << management->Karyawan[i] << endl;
            cout << "ID: " << management->ID_Karyawan[i] << endl;
            cout << "Tugas: " << management->Tugas[i] << endl;
            cout << "Status Absen: " << (management->absen[i] ? "Hadir" : "Tidak Hadir") << endl;
            cout << "Status Tugas: " << (management->status_tugas[i] ? "Sudah Dikerjakan" : "Belum Dikerjakan") << endl;
            karyawan_ditemukan = true;
            break;
        }
    }

    if (!karyawan_ditemukan) {
        cout << "Karyawan dengan ID tersebut tidak ditemukan." << endl;
    }
}

void lihat_absensi_karyawan(Management& management) {
    sorting(&management); // Panggil fungsi sorting sebelum menampilkan daftar
    cout << "|=================================================|" << endl;
    cout << "|              DAFTAR ABSENSI                     |" << endl;
    cout << "|=================================================|" << endl;
    cout << "| No | Nama Karyawan |  ID Karyawan  |  Status    |" << endl;
    cout << "|=================================================|" << endl;

    int nomor = 1;
    for (int i = 0; i < maxdata; ++i) {
        if (!management.Karyawan[i].empty()) {
            string status = management.status_absensi[i] ? "Hadir" : "Tidak Hadir";
            cout << "| " << nomor << " | " << management.Karyawan[i] << " | " << management.ID_Karyawan[i] << " | " << status << " |" << endl;
            nomor++;
        }
    }

    cout << "|=================================================|" << endl;
}

void lihat_tugas_karyawan(Management& management) {
    sorting(&management); // Panggil fungsi sorting sebelum menampilkan daftar
    cout << "|=============================================================|" << endl;
    cout << "|                        DAFTAR TUGAS                         |" << endl;
    cout << "|=============================================================|" << endl;
    cout << "| No | Nama Karyawan   | Tugas | ID Karyawan |     Status     |" << endl;
    cout << "|=============================================================|" << endl;

    int nomor = 1;
    for (int i = 0; i < maxdata; i++) {
        if (!management.Karyawan[i].empty()) {
            string status;
            if (!management.Tugas[i].empty()) {
                if (management.status_tugas[i]) {
                    status = "Sudah dikerjakan";
                } else {
                    status = "Belum dikerjakan";
                }
            } else {
                status = "Tidak ada tugas";
            }
            cout << "| " << nomor << " | " << management.Karyawan[i] << " | " << management.Tugas[i] << " | " << management.ID_Karyawan[i] << " | " << status << " |" << endl;
            nomor++;
        }
    }
    cout << "|=============================================================|" << endl;
}

void tampilkan_karyawan(Management& management) {
    // Membaca data karyawan dari file
    ifstream file("Karyawan.txt");
    if (file.is_open()) {
        for (int i = 0; i < maxdata; ++i) {
            management.Karyawan[i] = "";
            management.ID_Karyawan[i] = 0;
        }
        string line;
        int idx = 0;
        while (getline(file, line) && idx < maxdata) {
            stringstream ss(line);
            string id_str, nama;
            if (getline(ss, id_str, ',') && getline(ss, nama)) {
                int id = stoi(id_str);
                management.ID_Karyawan[idx] = id;
                management.Karyawan[idx] = nama;
                idx++;
            }
        }
        file.close();
    } else {
        cout << "Tidak bisa membuka file." << endl;
        return;
    }

    sorting(&management); // Panggil fungsi sorting sebelum menampilkan daftar
    cout << "Daftar Karyawan:" << endl;
    cout << "==================================" << endl;
    cout << "No.\tNama Karyawan\t\tID Karyawan" << endl;
    cout << "==================================" << endl;

    int nomor = 1;
    for (int i = 0; i < maxdata; ++i) {
        if (!management.Karyawan[i].empty()) {
            cout << nomor << ".\t" << management.Karyawan[i] << "\t\t" << management.ID_Karyawan[i] << endl;
            nomor++;
        }
    }
    cout << "==================================" << endl;
}

void tambah_karyawan(Management& management) {
    string nama_karyawan;
    int id_karyawan;
    bool karyawan_ada = false;

    cout << "Masukkan Nama Karyawan Baru: ";
    cin.ignore();
    getline(cin, nama_karyawan);

    cout << "Masukkan ID Karyawan Baru: ";
    cin >> id_karyawan;

    // Cek apakah karyawan dengan ID yang sama sudah ada
    for (int i = 0; i < maxdata; ++i) {
        if (management.ID_Karyawan[i] == id_karyawan) {
            cout << "ID Karyawan sudah ada. Silakan gunakan ID yang lain." << endl;
            karyawan_ada = true;
            break;
        }
    }

    // Jika karyawan belum ada, tambahkan ke array
    if (!karyawan_ada) {
        for (int i = 0; i < maxdata; ++i) {
            if (management.Karyawan[i].empty()) {
                management.Karyawan[i] = nama_karyawan;
                management.ID_Karyawan[i] = id_karyawan;
                management.absen[i] = false; // Inisialisasi status absen
                management.status_absensi[i] = false; // Inisialisasi status absensi
                cout << "Karyawan berhasil ditambahkan." << endl;

                // Menambahkan akun guest baru secara otomatis
                if (jumlah_akun < maxAkun) {
                    akun[jumlah_akun].username = nama_karyawan;
                    akun[jumlah_akun].password = id_karyawan;
                    akun[jumlah_akun].role = "guest";
                    jumlah_akun++;
                    cout << "Akun guest otomatis dibuat." << endl;
                    cout << "Username: " << nama_karyawan << endl;
                    cout << "Password: " << id_karyawan << endl;

                    // Menyimpan akun ke file
                    ofstream akunFile("Akun.txt", ios::app);
                    if (akunFile.is_open()) {
                        akunFile << nama_karyawan << "," << id_karyawan << ",guest\n";
                        akunFile.close();
                    } else {
                        cout << "Tidak bisa membuka file untuk menyimpan akun." << endl;
                    }
                } else {
                    cout << "Tidak bisa menambahkan akun baru, kapasitas penuh." << endl;
                }

                // Menulis data ke file teks
                ofstream file("Karyawan.txt", ios::app); // Membuka file untuk ditambahkan
                if (file.is_open()) {
                    file << id_karyawan << "," << nama_karyawan << "\n"; // Menulis data ke file
                    file.close(); // Menutup file
                    cout << "Karyawan berhasil ditambahkan ke database." << endl;
                } else {
                    cout << "Tidak bisa membuka file." << endl;
                }
                break;
            }
        }
    }
}

void loadAkun() {
    ifstream akunFile("Akun.txt");
    if (akunFile.is_open()) {
        string line;
        jumlah_akun = 0; // Reset jumlah akun sebelum memuat dari file
        while (getline(akunFile, line)) {
            stringstream ss(line);
            string username, password_str, role;
            getline(ss, username, ',');
            getline(ss, password_str, ',');
            getline(ss, role);

            if (jumlah_akun < maxAkun) {
                akun[jumlah_akun].username = username;
                akun[jumlah_akun].password = stoi(password_str);
                akun[jumlah_akun].role = role;
                jumlah_akun++;
            }
        }
        akunFile.close();
    } else {
        cout << "Tidak bisa membuka file akun." << endl;
    }
}

void saveAkun() {
    ofstream akunFile("Akun.txt");
    if (akunFile.is_open()) {
        for (int i = 0; i < jumlah_akun; ++i) {
            akunFile << akun[i].username << "," << akun[i].password << "," << akun[i].role << "\n";
        }
        akunFile.close();
    } else {
        cout << "Tidak bisa membuka file akun untuk penulisan." << endl;
    }
}

void hapusAkun(const string& username) {
    int index = -1;
    for (int i = 0; i < jumlah_akun; ++i) {
        if (akun[i].username == username) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < jumlah_akun - 1; ++i) {
            akun[i] = akun[i + 1];
        }
        jumlah_akun--;
        saveAkun();
        cout << "Akun dengan username " << username << " berhasil dihapus." << endl;
    } else {
        cout << "Akun dengan username " << username << " tidak ditemukan." << endl;
    }
}

void tambahkan_tugas_karyawan(Management* management){
    int id_karyawan;
    cout << "Masukkan ID karyawan yang ingin di tambahkan Tugas: ";
    cin >> id_karyawan;
    bool found = false; // Flag to track if the employee is found
    for (int i = 0; i < maxdata; i++) {
        if (management->ID_Karyawan[i] == id_karyawan) {
            string new_tugas;
            cout << "Masukkan Tugas untuk karyawan: ";
            cin.ignore();
            getline(cin, new_tugas);
            management->Tugas[i] = new_tugas;
            cout << "Tugas untuk karyawan dengan ID " << id_karyawan << " berhasil tambahkan." << endl;
            found = true; // Employee found and edited
            break; // No need to continue looping once the employee is found
        }
    }
    if (!found) { // If employee not found
        cout << "Karyawan dengan ID " << id_karyawan << " tidak ditemukan." << endl;
    }
}

void absen_karyawan(Management* management) {
    int id_karyawan;
    bool karyawan_ditemukan = false; // Tandai apakah karyawan berhasil ditemukan

    cout << "Masukkan ID Karyawan yang akan diabsen: ";
    cin >> id_karyawan;

    // Cari karyawan dengan ID yang sesuai
    for (int i = 0; i < maxdata; ++i) {
        if (management->ID_Karyawan[i] == id_karyawan) {
            management->absen[i] = true; // Set status absen menjadi true
            management->status_absensi[i] = true; // Set status absensi menjadi true
            cout << "Karyawan dengan ID " << id_karyawan << " berhasil diabsen." << endl;
            karyawan_ditemukan = true; // Tandai bahwa karyawan berhasil ditemukan
            break; // Keluar dari loop setelah karyawan berhasil diabsen
        }
    }

    // Jika karyawan tidak ditemukan, tampilkan pesan di luar loop
    if (!karyawan_ditemukan) {
        cout << "Karyawan dengan ID " << id_karyawan << " tidak terdaftar." << endl;
    }
}

void edit_tugas_karyawan(Management* management) {
    int id_karyawan;
    cout << "Masukkan ID karyawan yang ingin diubah tugasnya: ";
    cin >> id_karyawan;
    bool found = false; // Flag to track if the employee is found
    for (int i = 0; i < maxdata; i++) {
        if (management->ID_Karyawan[i] == id_karyawan) {
            string new_tugas;
            cout << "Masukkan Tugas baru untuk karyawan: ";
            cin.ignore();
            getline(cin, new_tugas);
            management->Tugas[i] = new_tugas;
            cout << "Tugas untuk karyawan dengan ID " << id_karyawan << " berhasil diubah." << endl;
            found = true; // Employee found and edited
            break; // No need to continue looping once the employee is found
        }
    }
    if (!found) { // If employee not found
        cout << "Karyawan dengan ID " << id_karyawan << " tidak ditemukan." << endl;
    }
}

void kerjakan_tugas_karyawan(Management& management) {
    int id_karyawan;
    cout << "Masukkan ID karyawan yang ingin mengerjakan tugas: ";
    cin >> id_karyawan;
    bool found = false;
    for (int i = 0; i < maxdata; i++) {
        if (management.ID_Karyawan[i] == id_karyawan) {
            if (!management.Tugas[i].empty() && !management.status_tugas[i]) {
                string pilihan;
                cout << "Tugas: " << management.Tugas[i] << endl;
                cout << "Kerjakan tugas? (ya/tidak): ";
                cin >> pilihan;
                if (pilihan == "ya" || pilihan == "YA") {
                    management.status_tugas[i] = true;
                    cout << "Tugas berhasil dikerjakan." << endl;
                    found = true;
                    break;
                } else {
                    cout << "Tugas tidak dikerjakan." << endl;
                }
            }if (management.status_tugas[i]) {
                cout << "Tugas sudah dikerjakan." << endl;
            }else {
                cout << "Tidak ada tugas untuk karyawan ini." << endl;
                found = true;
            }
            break;
        }
    }
    if (!found) {
        cout << "Karyawan dengan ID " << id_karyawan << " tidak ditemukan." << endl;
    }
}

void pecat_karyawan(Management& management) {
    int id_karyawan;
    bool karyawan_ditemukan = false;

    cout << "Masukkan ID Karyawan yang akan dipecat: ";
    cin >> id_karyawan;

    for (int i = 0; i < maxdata; ++i) {
        if (management.ID_Karyawan[i] == id_karyawan) {
            string username = management.Karyawan[i]; // Simpan username sebelum dihapus
            management.Karyawan[i] = "";
            management.ID_Karyawan[i] = 0;
            management.Tugas[i] = "";
            management.absen[i] = false;
            management.status_absensi[i] = false;
            management.status_tugas[i] = false;

            cout << "Karyawan berhasil dipecat." << endl;
            karyawan_ditemukan = true;

            hapusAkun(username); // Hapus akun setelah karyawan dipecat

            break;
        }
    }

    if (!karyawan_ditemukan) {
        cout << "Karyawan dengan ID tersebut tidak ditemukan." << endl;
    }

    ofstream file("Karyawan.txt");
    if (file.is_open()) {
        for (int i = 0; i < maxdata; ++i) {
            if (!management.Karyawan[i].empty()) {
                file << management.ID_Karyawan[i] << "," << management.Karyawan[i] << "\n";
            }
        }
        file.close();
        cout << "Data karyawan berhasil diperbarui." << endl;
    } else {
        cout << "Tidak bisa membuka file Karyawan.txt untuk penulisan." << endl;
    }
}

void hapus_tugas_karyawan(Management* management) {
    int id_tugas;
    bool tugas = false;
    cout << "Masukkan ID Tugas Karyawan yang akan dihapus: ";
    cin >> id_tugas;

    for (int i = 0; i < maxdata; i++) {
        if (management->ID_Karyawan[i] == id_tugas) {
            management->Tugas[i] = "";
            cout << "Tugas Karyawan Berhasil dihapus" << std::endl;
            tugas = true;
            break;
        }
    }
    
    if (!tugas) {
        cout << "Tugas Karyawan dengan ID tersebut tidak ditemukan" << std::endl;
    }
}

// Deklarasi Khsus Menu
bool registrasi();
bool menu_login();
void menu_admin();
void tugas_karyawan();
void Menu_list_karyawan();
void menu_guest();
// Main menu 
int main() {
    loadAkun();
    muat_data_karyawan(management);
    !menu_login();
    return 0;
}

bool menu_login() {
    string pilihan_login;
    int pilihan_login2;
    string username;
    int password;
    
    do {
        cout << "|===================================|" << endl;
        cout << "|              LOGIN                |" << endl;
        cout << "|===================================|" << endl;
        cout << "| 1. Login                          |" << endl;
        cout << "| 2. Keluar                         |" << endl;
        cout << "|===================================|" << endl;
        cout << "Masukkan pilihan Anda (1-2): ";
        try {
            cin >> pilihan_login;
            pilihan_login2 = stoi(pilihan_login);
        } catch (const exception& e) {
            cout << "Pilihan tidak valid" << endl;
            continue;
        }
        
        switch (pilihan_login2) {
            case 1:
                cout << "Masukkan Username: ";
                cin.ignore();
                getline(cin, username);
                cout << "Masukkan Password: ";
                cin >> password;

                // Cek username dan password
                for (int i = 0; i < jumlah_akun; ++i) {
                    if (akun[i].username == username && akun[i].password == password) {
                        if (akun[i].role == "admin") {
                            menu_admin();
                        } else if (akun[i].role == "guest") {
                            menu_guest();
                        }
                        return true;
                    }
                }
                cout << "Username atau Password salah." << endl;
                break;
            case 2:
                cout << "Keluar dari Program Silahkan tekan enter....." << endl;
                getch();
                exit(0);
                return false;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                break;
        }
    } while (pilihan_login2 != 2);
    
    return false;
}

void menu_admin(){
    string pilihan_admin;
    system("cls");
    int pilihan_admin2;
    do{
        cout<<"|====================================|"<<endl;
        cout<<"|              MENU ADMIN            |"<<endl;
        cout<<"|====================================|"<<endl;
        cout<<"|     1. Lihat absensi karyawan      |"<<endl;
        cout<<"|     2. Menu tugas karyawan         |"<<endl;
        cout<<"|     3. Menu list Karyawan          |"<<endl;
        cout<<"|     4. Searching ID Karyawan       |"<<endl;
        cout<<"|     5. Kembali Ke menu Login       |"<<endl;
        cout<<"|====================================|"<<endl;
        cout<<"Masukkan Pilihan (1-5): ";
        try
            {
            cin >> pilihan_admin;
            pilihan_admin2 = stoi(pilihan_admin);
            }
            catch(const exception& e)
            {
        cout << "Pilihan tidak valid" << endl;
        menu_admin();
        }
        switch (pilihan_admin2)
        {
        case 1:{
            lihat_absensi_karyawan(management);
            break;
        }
        case 2:{
            tugas_karyawan();
            break;
        }
        case 3:{
            Menu_list_karyawan();
            break;
        }
        case 4:{
             search(&management);
            break;
        }
        case 5:{
            cout<<"Kembali Ke Menu Login Silahkan tekan enter....."<<endl;
            getch();
            system("cls");
            menu_login();
            break;
        }
        default:
            cout<<"Pilihan Anda tidak Valid. Silahkan coba lagi"<<endl;
            break;
        }
    } while (pilihan_admin2 !=7);
}

void tugas_karyawan(){
    string pilihan_tugas_karyawan;
    system("cls");
    int pilihan_tugas_karyawan2;
    do
    {
        cout<<"|==============================|"<<endl;
        cout<<"|      MENU UTAMA KARYAWAN     |"<<endl;
        cout<<"|==============================|"<<endl;
        cout<<"|   1. LIHAT TUGAS KARYAWAN    |"<<endl;
        cout<<"|   2. TAMBAHKAN TUGAS KARYAWAN|"<<endl;
        cout<<"|   3. EDIT TUGAS KARYAWAN     |"<<endl;
        cout<<"|   4. HAPUS TUGAS KARYAWAN    |"<<endl;
        cout<<"|   5. KEMBALI KE MENU ADMIN   |"<<endl;
        cout<<"|==============================|"<<endl;
        cout<<"Masukkan Pilihan Anda (1-5): ";
        try
        {
            cin>>pilihan_tugas_karyawan; fflush(stdin);
            pilihan_tugas_karyawan2 = stoi(pilihan_tugas_karyawan);
        }
        catch(const exception& e){
            cout << "Pilihan tidak valid" << endl;
            tugas_karyawan();
        }
        switch (pilihan_tugas_karyawan2)
        {
        case 1:
            lihat_tugas_karyawan(management);
            break;
        case 2:
            tambahkan_tugas_karyawan(&management);
            break;
        
        case 3:
            edit_tugas_karyawan(&management);
            break;
        
        case 4:
            hapus_tugas_karyawan(&management);
            break;
        
        case 5:
            cout<<"Kembali Ke Menu Admin Silahkan tekan enter....."<<endl;
            getch();
            system("cls");
            menu_admin();
            break;
        default:
            cout<<"Pilihan anda tidak Valid"<<endl;
            break;
        }
    } while (pilihan_tugas_karyawan2 !=5);
}

void Menu_list_karyawan(){
    string pilihan_listkaryawan;
    system("cls");
    int pilihan_listkaryawan2;
    do{
        cout<<"|=================================|"<<endl;
        cout<<"|        MENU LIST KARYAWAN       |"<<endl;
        cout<<"|=================================|"<<endl;
        cout<<"|       1. TAMBAHKAN KARYAWAN     |"<<endl;
        cout<<"|       2. PECAT KARYAWAN         |"<<endl;
        cout<<"|       3. TAMPILKAN KARYAWAN     |"<<endl;
        cout<<"|       4. KEMBALI KE MENU ADMIN  |"<<endl;
        cout<<"|=================================|"<<endl;
        cout<<"Masukkan Pilihan (1-4): ";
        try
        {
            cin>>pilihan_listkaryawan;
            pilihan_listkaryawan2 = stoi(pilihan_listkaryawan);
        }
        catch(const exception& e){
            cout << "Pilihan tidak valid" << endl;
            Menu_list_karyawan();
            }
        switch (pilihan_listkaryawan2)
        {
        case 1:{
            tambah_karyawan(management);
            break;
        }
        case 2:{
            pecat_karyawan(management);
            break;
        }
        case 3:{
            tampilkan_karyawan(management);
            break;
        }
        case 4:{
            cout<<"Kembali Ke Menu Utama Silahkan tekan enter....."<<endl;
            getch();
            system("cls");
            menu_admin();
            break;
        }
        default:
            cout<<"Pilihan yang Anda masukkan tidak Valid. Silahkan Coba Lagi"<<endl;
            break;
        }
    }while (pilihan_listkaryawan2 != 4 );  
}

void menu_guest() {
    string pilihan_guest;
    int pilihan_guest2;
    
    do {
        cout << "|=============================|" << endl;
        cout << "|           MENU GUEST        |" << endl;
        cout << "|=============================|" << endl;
        cout << "|            1. ABSEN         |" << endl;
        cout << "|        2. MENU TUGAS        |" << endl;
        cout << "|   3. KEMBALI KE MENU UTAMA  |" << endl;
        cout << "|=============================|" << endl;
        cout << "Masukkan Pilihan Anda (1-3) : ";
        cin >> pilihan_guest;
        
        try {
            pilihan_guest2 = stoi(pilihan_guest);
        } catch(const exception& e) {
            cout << "Pilihan tidak valid" << endl;
            continue; // Lanjutkan iterasi saat ini
        }
        
        switch (pilihan_guest2) {
            case 1:
                absen_karyawan(&management);
                break;
            case 2: {
                string menu_tugas;
                int pilihan_karyawan2;
                
                do {
                    cout << "|==========================|" << endl;
                    cout << "|    MENU TUGAS KARYAWAN   |" << endl;
                    cout << "|==========================|" << endl;
                    cout << "|    1. LIHAT LIST TUGAS   |" << endl;
                    cout << "|    2. KERJAKAN TUGAS     |" << endl;
                    cout << "|   3. KEMBALI MENU GUEST  |" << endl;
                    cout << "|==========================|" << endl;
                    cout << "Masukkan Pilihan Anda (1-3): ";
                    getch();
                    cin >> menu_tugas;
                    
                    try {
                        pilihan_karyawan2 = stoi(menu_tugas);
                    } catch(const std::exception& e) {
                        cout << "Pilihan Anda Tidak Valid" << endl;
                        continue; // Lanjutkan iterasi saat ini
                    }

                    switch (pilihan_karyawan2) {
                        case 1:
                            lihat_tugas_karyawan(management);
                            break;
                        case 2:
                            kerjakan_tugas_karyawan(management);
                            break;
                        case 3:
                            cout<<"Tekan enter untuk kembali ke menu Guest..."<<endl;
                            getch();
                            system("cls");
                            menu_guest();
                            break;
                        default:
                            cout << "Pilihan Anda Tidak Valid" << endl;
                            break;
                    }
                } while (pilihan_karyawan2 != 3);
                break;
            }
            case 3:
                cout<<"Tekan enter untuk kembali ke menu awal"<<endl;
                getch();
                system("cls");
                menu_login();
                break;
            default:
                cout << "Pilihan Anda Tidak Valid" << endl;
                break;
        }
    } while (pilihan_guest2 != 3);
}