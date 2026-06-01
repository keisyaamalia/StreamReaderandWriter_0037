#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

struct Barang {
    int    id;
    string nama;
    string kategori;
    int    stok;
    double harga;
};

const string FILE_GUDANG = "gudang.txt";

class TokoElektronik {
private:
    string etalase[3];
public:
    TokoElektronik() {
        etalase[0] = "Laptop Gaming ASUS ROG  - Rp 18.500.000";
        etalase[1] = "Smartphone Samsung S24 Ultra - Rp 14.999.000";
        etalase[2] = "Smart TV LG OLED 55\"    - Rp 12.750.000";
    }
    string ambilProduk(size_t nomorRak) {
        try {
            vector<string> temp(etalase, etalase + 3);
            return temp.at(nomorRak);
        }
        catch (const out_of_range&) {
            throw string("Gagal Mengambil Barang : Rak nomor " +
                         to_string(nomorRak) +
                         " kosong atau tidak tersedia!");
        }
    }
};

Barang parseBaris(const string& baris) {
    Barang b;
    stringstream ss(baris);
    string token;
    getline(ss, token, '|'); b.id       = stoi(token);
    getline(ss, token, '|'); b.nama     = token;
    getline(ss, token, '|'); b.kategori = token;
    getline(ss, token, '|'); b.stok     = stoi(token);
    getline(ss, token, '|'); b.harga    = stod(token);
    return b;
}

string toBaris(const Barang& b) {
    return to_string(b.id) + "|" + b.nama + "|" + b.kategori + "|" +
           to_string(b.stok) + "|" + to_string(b.harga);
}

vector<Barang> bacaGudang() {
    vector<Barang> daftar;
    ifstream fin(FILE_GUDANG);
    if (!fin.is_open()) return daftar;
    string baris;
    while (getline(fin, baris)) {
        if (!baris.empty()) {
            try { daftar.push_back(parseBaris(baris)); }
            catch (...) {}
        }
    }
    fin.close();
    return daftar;
}

void simpanGudang(const vector<Barang>& daftar) {
    ofstream fout(FILE_GUDANG, ios::trunc);
    for (const auto& b : daftar) fout << toBaris(b) << "\n";
    fout.close();
}

int idTerbesar(const vector<Barang>& daftar) {
    int maks = 0;
    for (const auto& b : daftar) if (b.id > maks) maks = b.id;
    return maks;
}

void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}