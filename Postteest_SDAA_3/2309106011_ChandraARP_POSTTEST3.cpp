#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

#include <windows.h>
using namespace std;

// bersihkan layar
void bersihkanLayar() {
    system("cls");
}

// struct untuk ikan hias
struct IkanHias {
    string nama;
    double harga;
    int stok;
    string jenisIkan;
    IkanHias* next;  // Pointer ke node berikutnya

    IkanHias(string n, double h, int s, string j) : nama(n), harga(h), stok(s), jenisIkan(j), next(nullptr) {}
};

// Linked list nyimpan ikan hias
IkanHias* head = nullptr;
int jumlahIkanHias = 0;

// Struct riwayat transaksi
struct Transaksi {
    string namaIkan;
    int jumlah;
    double totalHarga;
    bool isPembelian;  // true jika pembelian, false jika penjualan
};

vector<Transaksi> riwayatTransaksi;

// Deklarasi fungsi
void tambahIkanHias();
void tampilkanIkanHias();
void updateIkanHias();
void hapusIkanHias();
void beliIkanHias();
void jualIkanHias();
void tampilkanRiwayatTransaksi();
void tampilkanMenu();
void tunggu();

int main() {
    int pilihan;
    do {
        bersihkanLayar();
        tampilkanMenu();
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        bersihkanLayar();
        switch (pilihan) {
            case 1:
                tambahIkanHias();
                break;
            case 2:
                tampilkanIkanHias();
                break;
            case 3:
                updateIkanHias();
                break;
            case 4:
                hapusIkanHias();
                break;
            case 5:
                beliIkanHias();
                break;
            case 6:
                jualIkanHias();
                break;
            case 7:
                tampilkanRiwayatTransaksi();
                break;
            case 8:
                cout << "Terima kasih telah menggunakan Sistem Jual Beli Ikan Hias!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
        if (pilihan != 8) tunggu();
    } while (pilihan != 8);

    // Membersihkan memori
    IkanHias* current = head;
    while (current != nullptr) {
        IkanHias* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}

void tampilkanMenu() {
    cout << "===== SISTEM JUAL BELI IKAN HIAS =====" << endl;
    cout << "1. Tambah Ikan Hias" << endl;
    cout << "2. Tampilkan Daftar Ikan Hias" << endl;
    cout << "3. Update Informasi Ikan Hias" << endl;
    cout << "4. Hapus Ikan Hias" << endl;
    cout << "5. Beli Ikan Hias" << endl;
    cout << "6. Jual Ikan Hias" << endl;
    cout << "7. Tampilkan Riwayat Transaksi" << endl;
    cout << "8. Keluar" << endl;
}

void tambahIkanHias() {
    string nama, jenisIkan;
    double harga;
    int stok;

    cin.ignore();
    cout << "Masukkan nama ikan hias: ";
    getline(cin, nama);
    cout << "Masukkan jenis ikan hias: ";
    getline(cin, jenisIkan);
    cout << "Masukkan harga ikan hias: ";
    cin >> harga;
    cout << "Masukkan stok ikan hias: ";
    cin >> stok;

    IkanHias* newIkan = new IkanHias(nama, harga, stok, jenisIkan);
    
    if (head == nullptr) {
        head = newIkan;
    } else {
        IkanHias* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newIkan;
    }
    
    jumlahIkanHias++;
    cout << "Ikan hias berhasil ditambahkan!" << endl;
}

void tampilkanIkanHias() {
    if (head == nullptr) {
        cout << "Belum ada ikan hias dalam daftar." << endl;
        return;
    }

    cout << "===== DAFTAR IKAN HIAS =====" << endl;
    cout << setw(5) << "No" << setw(20) << "Nama" << setw(20) << "Jenis" << setw(15) << "Harga" << setw(10) << "Stok" << endl;
    
    IkanHias* current = head;
    int index = 1;
    while (current != nullptr) {
        cout << setw(5) << index << setw(20) << current->nama 
             << setw(20) << current->jenisIkan
             << setw(15) << fixed << setprecision(2) << current->harga 
             << setw(10) << current->stok << endl;
        current = current->next;
        index++;
    }
}

void updateIkanHias() {
    if (head == nullptr) {
        cout << "Belum ada ikan hias dalam daftar." << endl;
        return;
    }

    tampilkanIkanHias();
    int indeks;
    cout << "Masukkan nomor ikan hias yang ingin diupdate: ";
    cin >> indeks;

    if (indeks > 0 && indeks <= jumlahIkanHias) {
        IkanHias* current = head;
        for (int i = 1; i < indeks; i++) {
            current = current->next;
        }

        cin.ignore();
        cout << "Masukkan nama ikan hias baru (kosongin kl nd mau ubah): ";
        string namaBaru;
        getline(cin, namaBaru);
        if (!namaBaru.empty()) {
            current->nama = namaBaru;
        }

        cout << "Masukkan jenis ikan hias baru (kosongin kl nd mau ubah): ";
        string jenisBaru;
        getline(cin, jenisBaru);
        if (!jenisBaru.empty()) {
            current->jenisIkan = jenisBaru;
        }

        cout << "Masukkan harga ikan hias baru (ktik 0 kl nd mau ubah): ";
        double hargaBaru;
        cin >> hargaBaru;
        if (hargaBaru != 0) {
            current->harga = hargaBaru;
        }

        cout << "Masukkan stok ikan hias baru (ketik -1 kl nd mau ubah): ";
        int stokBaru;
        cin >> stokBaru;
        if (stokBaru != -1) {
            current->stok = stokBaru;
        }

        cout << "Informasi ikan hias berhasil diupdate!!!" << endl;
    } else {
        cout << "Nomor ikan hias tidak valid." << endl;
    }
}

void hapusIkanHias() {
    if (head == nullptr) {
        cout << "Belum ada ikan hias dalam daftar." << endl;
        return;
    }

    tampilkanIkanHias();
    int indeks;
    cout << "Masukkan nomor ikan hias yang ingin dihapus: ";
    cin >> indeks;

    if (indeks > 0 && indeks <= jumlahIkanHias) {
        IkanHias* toDelete;
        if (indeks == 1) {
            toDelete = head;
            head = head->next;
        } else {
            IkanHias* current = head;
            for (int i = 1; i < indeks - 1; i++) {
                current = current->next;
            }
            toDelete = current->next;
            current->next = toDelete->next;
        }
        delete toDelete;
        jumlahIkanHias--;
        cout << "Ikan hias berhasil dihapus!" << endl;
    } else {
        cout << "Nomor ikan hias tidak valid." << endl;
    }
}

void beliIkanHias() {
    tampilkanIkanHias();
    int indeks, jumlah;
    cout << "Masukkan nomor ikan hias yang ingin dibeli: ";
    cin >> indeks;
    cout << "Masukkan jumlah yang ingin dibeli: ";
    cin >> jumlah;

    if (indeks > 0 && indeks <= jumlahIkanHias) {
        IkanHias* current = head;
        for (int i = 1; i < indeks; i++) {
            current = current->next;
        }

        if (jumlah > 0 && jumlah <= current->stok) {
            double totalHarga = current->harga * jumlah;
            current->stok -= jumlah;
            
            cout << "Pembelian berhasil!" << endl;
            cout << "Total harga: " << fixed << setprecision(2) << totalHarga << endl;

            // Menambahkan ke riwayat transaksi
            riwayatTransaksi.push_back({current->nama, jumlah, totalHarga, true});
        } else {
            cout << "Jumlah pembelian tidak valid atau stok tidak mencukupi." << endl;
        }
    } else {
        cout << "Nomor ikan hias tidak valid." << endl;
    }
}

void jualIkanHias() {
    tampilkanIkanHias();
    int indeks, jumlah;
    cout << "Masukkan nomor ikan hias yang ingin dijual: ";
    cin >> indeks;
    cout << "Masukkan jumlah yang ingin dijual: ";
    cin >> jumlah;

    if (indeks > 0 && indeks <= jumlahIkanHias) {
        IkanHias* current = head;
        for (int i = 1; i < indeks; i++) {
            current = current->next;
        }

        if (jumlah > 0) {
            double totalHarga = current->harga * jumlah;
            current->stok += jumlah;
            
            cout << "Penjualan berhasil!" << endl;
            cout << "Total harga: " << fixed << setprecision(2) << totalHarga << endl;

            // riwayat transaksi
            riwayatTransaksi.push_back({current->nama, jumlah, totalHarga, false});
        } else {
            cout << "Jumlah penjualan tidak valid." << endl;
        }
    } else {
        cout << "Nomor ikan hias tidak valid." << endl;
    }
}

void tampilkanRiwayatTransaksi() {
    if (riwayatTransaksi.empty()) {
        cout << "Belum ada riwayat transaksi." << endl;
        return;
    }

    cout << "===== RIWAYAT TRANSAKSI =====" << endl;
    cout << setw(5) << "No" << setw(20) << "Nama Ikan" << setw(15) << "Jumlah" << setw(20) << "Total Harga" << setw(15) << "Jenis" << endl;
    for (size_t i = 0; i < riwayatTransaksi.size(); i++) {
        cout << setw(5) << i+1 << setw(20) << riwayatTransaksi[i].namaIkan
             << setw(15) << riwayatTransaksi[i].jumlah
             << setw(20) << fixed << setprecision(2) << riwayatTransaksi[i].totalHarga
             << setw(15) << (riwayatTransaksi[i].isPembelian ? "Pembelian" : "Penjualan") << endl;
    }
}

void tunggu() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}