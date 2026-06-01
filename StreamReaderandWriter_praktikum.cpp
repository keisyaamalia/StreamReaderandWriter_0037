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

void tampilkanDaftar(const vector<Barang>& daftar) {
    cout << "\n" << string(74, '=') << "\n";
    cout << left << setw(5) << "ID" << setw(25) << "Nama Barang"
         << setw(15) << "Kategori" << setw(7) << "Stok" << "Harga\n";
    cout << string(74, '-') << "\n";
    if (daftar.empty()) {
        cout << "  (Gudang kosong)\n";
    } else {
        for (const auto& b : daftar) {
            cout << left << setw(5) << b.id << setw(25) << b.nama
                 << setw(15) << b.kategori << setw(7) << b.stok
                 << "Rp " << fixed << setprecision(0) << b.harga << "\n";
        }
    }
    cout << string(74, '=') << "\n";
}

void lihatBarang() {
    cout << "\n===== DAFTAR BARANG GUDANG =====";
    vector<Barang> daftar = bacaGudang();
    tampilkanDaftar(daftar);
    cout << "Total: " << daftar.size() << " barang.\n";
}

void tambahBarang() {
    cout << "\n===== TAMBAH BARANG BARU =====\n";
    vector<Barang> daftar = bacaGudang();
    Barang b;
    b.id = idTerbesar(daftar) + 1;
    clearInput();
    cout << "Nama Barang  : "; getline(cin, b.nama);
    cout << "Kategori     : "; getline(cin, b.kategori);
    cout << "Stok         : "; cin >> b.stok;
    cout << "Harga (Rp)   : "; cin >> b.harga;
    daftar.push_back(b);
    simpanGudang(daftar);
    cout << "\n[OK] Barang \"" << b.nama << "\" (ID: " << b.id
         << ") berhasil ditambahkan ke gudang.\n";
}

void updateBarang() {
    vector<Barang> daftar = bacaGudang();
    tampilkanDaftar(daftar);
    if (daftar.empty()) { cout << "Tidak ada data untuk diubah.\n"; return; }
    int targetId;
    cout << "Masukkan ID barang yang akan diperbarui: "; cin >> targetId;
    auto it = find_if(daftar.begin(), daftar.end(),
                      [&](const Barang& b){ return b.id == targetId; });
    if (it == daftar.end()) {
        cout << "[ERROR] Barang dengan ID " << targetId << " tidak ditemukan.\n";
        return;
    }
    cout << "\nData saat ini:\n";
    cout << "  Nama     : " << it->nama     << "\n";
    cout << "  Kategori : " << it->kategori << "\n";
    cout << "  Stok     : " << it->stok     << "\n";
    cout << "  Harga    : Rp " << fixed << setprecision(0) << it->harga << "\n";
    clearInput();
    cout << "\nMasukkan data baru (kosongkan Enter = tidak berubah):\n";
    string tmp;
    cout << "Nama Barang  [" << it->nama     << "]: ";
    getline(cin, tmp); if (!tmp.empty()) it->nama = tmp;
    cout << "Kategori     [" << it->kategori << "]: ";
    getline(cin, tmp); if (!tmp.empty()) it->kategori = tmp;
    cout << "Stok         [" << it->stok     << "]: ";
    getline(cin, tmp); if (!tmp.empty()) it->stok = stoi(tmp);
    cout << "Harga (Rp)   [" << fixed << setprecision(0) << it->harga << "]: ";
    getline(cin, tmp); if (!tmp.empty()) it->harga = stod(tmp);
    simpanGudang(daftar);
    cout << "\n[OK] Data barang ID " << targetId << " berhasil diperbarui.\n";
}