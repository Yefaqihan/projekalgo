#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

struct Servis
{
    char id[12];
    char nama[30];
    char noHP[15];
    char tipeHP[20];
    char kerusakan[15];
    char status[15];
    char estimasiBiaya[20];
    Servis *next;
};

Servis *kepala = nullptr;

void tambahKeList(Servis *baru)
{
    baru->next = nullptr;
    if (kepala == nullptr)
    {
        kepala = baru;
    }
    else
    {
        Servis *bantu = kepala;
        while (bantu->next != nullptr)
            bantu = bantu->next;
        bantu->next = baru;
    }
}

void bacaFileKeList()
{
    FILE *serv = fopen("serv.dat", "rb");
    if (serv == nullptr)
        return;

    Servis bantu;
    while (fread(&bantu, sizeof(Servis) - sizeof(Servis *), 1, serv))
    {
        Servis *baru = new Servis;
        *baru = bantu;
        baru->next = nullptr;
        tambahKeList(baru);
    }
    fclose(serv);
}

void tampilkanData()
{
    cout << "\n=== Daftar Semua Data Servis HP ===" << endl;
    Servis *bantu = kepala;
    while (bantu != nullptr)
    {
        cout << "ID Pelanggan    : " << bantu->id << endl;
        cout << "Nama Pelanggan  : " << bantu->nama << endl;
        cout << "Nomor HP        : " << bantu->noHP << endl;
        cout << "Tipe HP         : " << bantu->tipeHP << endl;
        cout << "Kerusakan       : " << bantu->kerusakan << endl;
        cout << "Status          : " << bantu->status << endl;
        cout << "Estimasi Biaya  : " << bantu->estimasiBiaya << endl;
        cout << "------------------------------" << endl;
        bantu = bantu->next;
    }
}

void tambahData()
{
    FILE *serv = fopen("serv.dat", "ab");
    if (serv == nullptr)
    {
        cout << "Error membuka file!" << endl;
        exit(1);
    }

    int tambah;
    cout << "Masukkan jumlah servis-an yang akan ditambahkan: ";
    cin >> tambah;
    cin.ignore();

    for (int i = 0; i < tambah; ++i)
    {
        Servis *baru = new Servis;

        cout << "\nDaftar Data Servis ke-" << i + 1 << endl;
        cout << "ID Pelanggan : ";
        cin.getline(baru->id, 12);
        cout << "Nama Pelanggan : ";
        cin.getline(baru->nama, 30);
        cout << "Nomor HP : ";
        cin.getline(baru->noHP, 15);
        cout << "Tipe HP Pelanggan : ";
        cin.getline(baru->tipeHP, 20);
        cout << "Jenis Kerusakan : ";
        cin.getline(baru->kerusakan, 15);
        cout << "Status Servis : ";
        cin.getline(baru->status, 15);
        cout << "Estimasi Biaya : ";
        cin.getline(baru->estimasiBiaya, 20);

        fwrite(baru, sizeof(Servis) - sizeof(Servis *), 1, serv);
        tambahKeList(baru);
    }

    fclose(serv);
}

void cariByID()
{
    char cari[12];
    cout << "Masukkan ID yang dicari: ";
    cin.ignore();
    cin.getline(cari, 12);

    Servis *bantu = kepala;
    bool ditemukan = false;
    while (bantu != nullptr)
    {
        if (strcmp(bantu->id, cari) == 0)
        {
            cout << "Data ditemukan:" << endl;
            cout << "Nama Pelanggan  : " << bantu->nama << endl;
            cout << "Nomor HP        : " << bantu->noHP << endl;
            cout << "Tipe HP         : " << bantu->tipeHP << endl;
            cout << "Kerusakan       : " << bantu->kerusakan << endl;
            cout << "Status          : " << bantu->status << endl;
            cout << "Estimasi Biaya  : " << bantu->estimasiBiaya << endl;
            ditemukan = true;
            break;
        }
        bantu = bantu->next;
    }

    if (!ditemukan)
        cout << "Data dengan ID tersebut tidak ditemukan." << endl;
}

void cariByNama()
{
    char cari[30];
    cout << "Masukkan Nama yang dicari: ";
    cin.ignore();
    cin.getline(cari, 30);

    Servis *bantu = kepala;
    bool ditemukan = false;
    while (bantu != nullptr)
    {
        if (strcmp(bantu->nama, cari) == 0)
        {
            cout << "\nID Pelanggan    : " << bantu->id << endl;
            cout << "Nama Pelanggan  : " << bantu->nama << endl;
            cout << "Nomor HP        : " << bantu->noHP << endl;
            cout << "Tipe HP         : " << bantu->tipeHP << endl;
            cout << "Kerusakan       : " << bantu->kerusakan << endl;
            cout << "Status          : " << bantu->status << endl;
            cout << "Estimasi Biaya  : " << bantu->estimasiBiaya << endl;
            ditemukan = true;
        }
        bantu = bantu->next;
    }

    if (!ditemukan)
        cout << "Data dengan nama tersebut tidak ditemukan." << endl;
}

int main()
{
    int pilihan;
    bacaFileKeList();

    do
    {
        cout << "\n===== MENU SERVIS HP =====" << endl;
        cout << "1. Tambah Data Servis" << endl;
        cout << "2. Tampilkan Semua Data" << endl;
        cout << "3. Cari Data by ID" << endl;
        cout << "4. Cari Data by Nama" << endl;
        cout << "5. Hapus Data Servis\n";
        cout << "6. Update Status Servis\n";
        cout << "7. Sorting Data by ID\n";
        cout << "0. Keluar" << endl;
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
            cout << "Fitur belum dibuat";
            break;
        case 6:
            cout << "Fitur belum dibuat";
            break;
        case 7:
            cout << "Fitur belum dibuat";
            break;
        case 0:
            cout << "Terima kasih. Keluar dari program." << endl;
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 0);

    return 0;
}
