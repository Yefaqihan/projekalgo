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
