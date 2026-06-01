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