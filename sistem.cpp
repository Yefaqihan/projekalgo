#include <iostream>

using namespace std;

const int MAX = 100;

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

// Untuk linked list (Menu 2)
struct Node {
    Servis data;
    Node* next;
};
