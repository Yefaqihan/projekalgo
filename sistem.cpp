#include <iostream>

using namespace std;

const int MAX = 100;

// string nya dirubah pakai char
struct Servis {
    int id;
    string nama;
    string noHP;
    string tipeHP;
    string kerusakan;
    int estimasiBiaya;
    string status;
};

Servis dataServis[MAX];
int jumlahData = 0;

int main() {
    int pilihan;

    do {
        cout << "\n===== MENU SERVIS HP =====\n";
        cout << "1. Tambah Data Servis\n";
        cout << "2. Tampilkan Semua Data\n";
        cout << "3. Cari Data (ID)\n";
        cout << "4. Cari Data (Nama Pelanggan)\n";
        cout << "5. Hapus Data Servis\n";
        cout << "6. Update Status Servis\n";
        cout << "7. Sorting Data by ID\n";
        cout << "0. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahData(); break;
            case 2: tampilkanData(); break;
            case 3: cariByID(); break;
            case 4: cariByNama(); break;
            case 5: hapusData(); break;
            case 6: updateStatus(); break;
            case 7: sortingData(); break;
            case 0: cout << "Terima kasih. Keluar dari program.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    return 0;
}
