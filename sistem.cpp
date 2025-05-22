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

void hapusDataByID()
{
    if (kepala == nullptr)
    {
        cout << "Tidak ada data untuk dihapus." << endl;
        return;
    }

    char idHapus[12];
    cout << "Masukkan ID yang akan dihapus: ";
    cin.ignore();
    cin.getline(idHapus, 12);

    Servis *bantu = kepala;
    Servis *sebelum = nullptr;

    while (bantu != nullptr && strcmp(bantu->id, idHapus) != 0)
    {
        sebelum = bantu;
        bantu = bantu->next;
    }

    if (bantu == nullptr)
    {
        cout << "Data dengan ID tersebut tidak ditemukan." << endl;
        return;
    }

    if (sebelum == nullptr)
    {
        // Hapus kepala
        kepala = bantu->next;
    }
    else
    {
        // Hapus node di tengah/akhir
        sebelum->next = bantu->next;
    }

    delete bantu;
    cout << "Data berhasil dihapus dari list." << endl;

    // Simpan perubahan ke file
    FILE *serv = fopen("serv.dat", "wb");
    if (serv == nullptr)
    {
        cout << "Gagal membuka file untuk menyimpan data." << endl;
        return;
    }

    Servis *simpan = kepala;
    while (simpan != nullptr)
    {
        fwrite(simpan, sizeof(Servis) - sizeof(Servis *), 1, serv);
        simpan = simpan->next;
    }

    fclose(serv);
}

void updateStatusServis()
{
    if (kepala == nullptr)
    {
        cout << "Tidak ada data untuk diupdate." << endl;
        return;
    }

    char idCari[12];
    cout << "Masukkan ID pelanggan yang ingin diupdate statusnya: ";
    cin.ignore();
    cin.getline(idCari, 12);

    Servis *bantu = kepala;
    bool ditemukan = false;
    while (bantu != nullptr)
    {
        if (strcmp(bantu->id, idCari) == 0)
        {
            cout << "Status saat ini: " << bantu->status << endl;
            cout << "Masukkan status baru: ";
            cin.getline(bantu->status, 15);
            ditemukan = true;
            break;
        }
        bantu = bantu->next;
    }

    if (!ditemukan)
    {
        cout << "Data dengan ID tersebut tidak ditemukan." << endl;
        return;
    }

    // Tulis ulang ke file
    FILE *serv = fopen("serv.dat", "wb");
    if (serv == nullptr)
    {
        cout << "Gagal membuka file untuk menyimpan update." << endl;
        return;
    }

    bantu = kepala;
    while (bantu != nullptr)
    {
        fwrite(bantu, sizeof(Servis) - sizeof(Servis *), 1, serv);
        bantu = bantu->next;
    }

    fclose(serv);
    cout << "Status berhasil diupdate dan disimpan ke file." << endl;
}

void sortingByID()
{
    if (kepala == nullptr || kepala->next == nullptr)
    {
        cout << "Data terlalu sedikit untuk disorting." << endl;
        return;
    }

    for (Servis *i = kepala; i != nullptr; i = i->next)
    {
        for (Servis *j = i->next; j != nullptr; j = j->next)
        {
            if (strcmp(i->id, j->id) > 0)
            {
                // Tukar semua data kecuali pointer next
                Servis temp = *i;
                *i = *j;
                *j = temp;

                // Kembalikan pointer next ke posisi semula
                Servis *tempNext = i->next;
                i->next = j->next;
                j->next = tempNext;
            }
        }
    }

    cout << "Data berhasil diurutkan berdasarkan ID." << endl;
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
            hapusDataByID();
            break;
        case 6:
            updateStatusServis();
            break;
        case 7:
            sortingByID();
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
