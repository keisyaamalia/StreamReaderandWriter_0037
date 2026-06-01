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