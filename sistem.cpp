#include <iostream>
#include <cstring>

using namespace std;

const int maxserv = 100;

struct Servis
{
    char id[1];
    char nama[30];
    char noHP[12];
    char tipeHP[20];
    char kerusakan[15];
    char status[15];
    char estimasiBiaya[20];
};

FILE *serv;
FILE *temp;
Servis dataServis[maxserv];
int jumlahHP = 0;

void tambahData()
{
    serv = fopen("serv.dat", "ab");

    if (serv == NULL)
    {
        cout << "Error!" << endl;
        exit(1);
    }

    int tambah;
    cout << "Masukkan jumlah servis-an yang akan ditambahkan: ";
    cin >> tambah;
    cin.ignore();

    for (int i = 0; i < tambah; ++i)
    {
        cout << "Daftar Data Servis ke - " << jumlahHP + 1 << endl;
        cout << "ID Pelanggan : ";
        cin.getline(dataServis[jumlahHP].id, 1);
        cout << "Nama Pelanggan : ";
        cin.getline(dataServis[jumlahHP].nama, 30);
        cout << "Nomor HP : ";
        cin.getline(dataServis[jumlahHP].noHP, 12);
        cout << "Tipe HP Pelanggan : ";
        cin.getline(dataServis[jumlahHP].tipeHP, 20);
        cout << "Jenis Kerusakan : ";
        cin.getline(dataServis[jumlahHP].kerusakan, 15);
        cout << "Status Servis : ";
        cin.getline(dataServis[jumlahHP].status, 15);
        cout << "Estimasi Biaya : ";
        cin.getline(dataServis[jumlahHP].estimasiBiaya, 20);

        cout << endl;
        fwrite(&dataServis[jumlahHP], sizeof(Servis), 1, serv);
        jumlahHP++;
    }
    fclose(serv);
}

int main()
{
    int pilihan;

    do
    {
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

        switch (pilihan)
        {
        case 1:
            tambahData();
            break;
        case 2:
            tampilkanData();
            break;
        case 3:
            cariByID();
            break;
        case 4:
            cariByNama();
            break;
        case 5:
            hapusData();
            break;
        case 6:
            updateStatus();
            break;
        case 7:
            sortingData();
            break;
        case 0:
            cout << "Terima kasih. Keluar dari program.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    return 0;
}
