#include <iostream>
#include <cstring>
#include <cstdlib>
// #include <fstream>

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

FILE *serv;
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
    serv = fopen("serv.dat", "rb");
    if (serv == nullptr)
        return;

    Servis temp;
    while (fread(&temp, sizeof(Servis) - sizeof(Servis *), 1, serv))
    {
        Servis *baru = new Servis;
        *baru = temp;
        baru->next = nullptr;
        tambahKeList(baru);
    }

    fclose(serv);
}

void tampilkanData()
{
    if (kepala == NULL)
    {
        cout << "Belum ada data servis yang tersimpan.\n";
        return;
    }
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
    serv = fopen("serv.dat", "ab");
    if (serv == NULL)
    {
        cout << "Error membuka file!" << endl;
        return;
    }

    int tambah;
    cout << "Masukkan jumlah servis-an yang akan ditambahkan: ";
    cin >> tambah;
    cin.ignore();

    for (int i = 0; i < tambah; ++i)
    {
        Servis *baru = new Servis;

        cout << "\nData Servis ke-" << i + 1 << endl;
        cout << "ID Pelanggan     : ";
        cin.getline(baru->id, 12);
        cout << "Nama Pelanggan   : ";
        cin.getline(baru->nama, 30);
        cout << "Nomor HP         : ";
        cin.getline(baru->noHP, 15);
        cout << "Tipe HP          : ";
        cin.getline(baru->tipeHP, 20);
        cout << "Jenis Kerusakan  : ";
        cin.getline(baru->kerusakan, 15);
        cout << "Status Servis    : ";
        cin.getline(baru->status, 15);
        cout << "Estimasi Biaya   : ";
        cin.getline(baru->estimasiBiaya, 20);

        fwrite(baru, sizeof(Servis) - sizeof(Servis *), 1, serv);
        tambahKeList(baru);
    }

    fclose(serv);

    cout << "Data servis telah berhasil ditambahkan";
}

void cariByID()
{
    if (kepala == nullptr)
    {
        cout << "Belum ada data untuk dicari.\n";
        return;
    }

    char cari[12];
    cin.ignore();
    cout << "Masukkan ID yang dicari: ";
    cin.getline(cari, 12);

    Servis *bantu = kepala;
    while (bantu != nullptr)
    {
        if (strcmp(bantu->id, cari) == 0)
        {
            cout << "\nData ditemukan:\n";
            cout << "Nama Pelanggan  : " << bantu->nama << endl;
            cout << "Nomor HP        : " << bantu->noHP << endl;
            cout << "Tipe HP         : " << bantu->tipeHP << endl;
            cout << "Kerusakan       : " << bantu->kerusakan << endl;
            cout << "Status          : " << bantu->status << endl;
            cout << "Estimasi Biaya  : " << bantu->estimasiBiaya << endl;
            return;
        }
        bantu = bantu->next;
    }

    cout << "Data dengan ID tersebut tidak ditemukan.\n";
}

void cariByNama()
{
    if (kepala == nullptr)
    {
        cout << "Belum ada data untuk dicari.\n";
        return;
    }

    char cari[30];
    cin.ignore();
    cout << "Masukkan Nama yang dicari: ";
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
        cout << "Data dengan nama tersebut tidak ditemukan.\n";
}

void hapusDataByID()
{
    if (kepala == nullptr)
    {
        cout << "Tidak ada data untuk dihapus.\n";
        return;
    }

    char idHapus[12];
    cin.ignore();
    cout << "Masukkan ID yang akan dihapus: ";
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
        cout << "Data tidak ditemukan.\n";
        return;
    }

    if (sebelum == nullptr)
    {
        kepala = bantu->next;
    }
    else
    {
        sebelum->next = bantu->next;
    }

    delete bantu;
    cout << "Data berhasil dihapus dari list.\n";

    FILE *file = fopen("serv.dat", "wb");
    if (file == nullptr)
    {
        cout << "Gagal menyimpan perubahan ke file.\n";
        return;
    }

    Servis *simpan = kepala;
    while (simpan != nullptr)
    {
        fwrite(simpan, sizeof(Servis) - sizeof(Servis *), 1, file);
        simpan = simpan->next;
    }

    fclose(file);
}

void updateStatusServis()
{
    if (kepala == nullptr)
    {
        cout << "Tidak ada data untuk diupdate.\n";
        return;
    }

    char idCari[12];
    cin.ignore();
    cout << "Masukkan ID pelanggan yang ingin diupdate: ";
    cin.getline(idCari, 12);

    Servis *bantu = kepala;
    while (bantu != nullptr)
    {
        if (strcmp(bantu->id, idCari) == 0)
        {
            cout << "Status lama: " << bantu->status << endl;
            cout << "Masukkan status baru: ";
            cin.getline(bantu->status, 15);

            FILE *file = fopen("serv.dat", "wb");
            if (file == nullptr)
            {
                cout << "Gagal menyimpan perubahan ke file.\n";
                return;
            }

            Servis *simpan = kepala;
            while (simpan != nullptr)
            {
                fwrite(simpan, sizeof(Servis) - sizeof(Servis *), 1, file);
                simpan = simpan->next;
            }
            fclose(file);

            cout << "Status berhasil diperbarui.\n";
            return;
        }
        bantu = bantu->next;
    }

    cout << "Data tidak ditemukan.\n";
}

void sortingByID()
{
    if (kepala == nullptr || kepala->next == nullptr)
    {
        cout << "Tidak cukup data untuk disorting.\n";
        return;
    }

    for (Servis *i = kepala; i != nullptr; i = i->next)
    {
        for (Servis *j = i->next; j != nullptr; j = j->next)
        {
            if (strcmp(i->id, j->id) > 0)
            {
                swap(*i, *j);
                swap(i->next, j->next); // kembalikan pointer next
            }
        }
    }

    cout << "Data berhasil diurutkan berdasarkan ID.\n";
}

int main()
{
    int pilihan;
    bacaFileKeList();

    do
    {
        system("cls");
        cout << "\n===== MENU SERVIS HP =====\n";
        cout << "1. Tambah Data Servis\n";
        cout << "2. Tampilkan Semua Data\n";
        cout << "3. Cari Data by ID\n";
        cout << "4. Cari Data by Nama\n";
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
            hapusDataByID();
            break;
        case 6:
            updateStatusServis();
            break;
        case 7:
            sortingByID();
            break;
        case 0:
            cout << "Terima kasih. Keluar dari program.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
        
        cout << "Tekan enter untuk kembali ke menu.....";
        cin.ignore();
        cin.get();

    } while (pilihan != 0);

    return 0;
}
