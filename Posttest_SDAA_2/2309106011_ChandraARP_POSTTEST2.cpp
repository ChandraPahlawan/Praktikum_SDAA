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

// struct
struct IkanHias {
    string nama;
    double harga;
    int stok;
    string jenisIkan;
};

// array dan pointer
const int KAPASITAS_MAKSIMAL = 100;
IkanHias* daftarIkanHias[KAPASITAS_MAKSIMAL];
int jumlahIkanHias = 0;

// Struct riwayat transaksi
struct Transaksi {
    string namaIkan;
    int jumlah;
    double totalHarga;
    bool isPembelian;  // true jika pembelian, false jika penjualan
};

vector<Transaksi> riwayatTransaksi;

// Deklarasi
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
    for (int i = 0; i < jumlahIkanHias; i++) {
        delete daftarIkanHias[i];
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
    if (jumlahIkanHias < KAPASITAS_MAKSIMAL) {
        IkanHias* ikanBaru = new IkanHias;
        cin.ignore();
        cout << "Masukkan nama ikan hias: ";
        getline(cin, ikanBaru->nama);
        cout << "Masukkan jenis ikan hias: ";
        getline(cin, ikanBaru->jenisIkan);
        cout << "Masukkan harga ikan hias: ";
        cin >> ikanBaru->harga;
        cout << "Masukkan stok ikan hias: ";
        cin >> ikanBaru->stok;

        daftarIkanHias[jumlahIkanHias] = ikanBaru;
        jumlahIkanHias++;

        cout << "Ikan hias berhasil ditambahkan!" << endl;
    } else {
        cout << "Penuh lekk ku msa ku taro di paret." << endl;
    }
}

void tampilkanIkanHias() {
    if (jumlahIkanHias == 0) {
        cout << "Belum ada ikan hias dalam daftar." << endl;
        return;
    }

    cout << "===== DAFTAR IKAN HIAS =====" << endl;
    cout << setw(5) << "No" << setw(20) << "Nama" << setw(20) << "Jenis" << setw(15) << "Harga" << setw(10) << "Stok" << endl;
    for (int i = 0; i < jumlahIkanHias; i++) {
        cout << setw(5) << i+1 << setw(20) << daftarIkanHias[i]->nama 
             << setw(20) << daftarIkanHias[i]->jenisIkan
             << setw(15) << fixed << setprecision(2) << daftarIkanHias[i]->harga 
             << setw(10) << daftarIkanHias[i]->stok << endl;
    }
}

void updateIkanHias() {
    if (jumlahIkanHias == 0) {
        cout << "Belum ada ikan hias dalam daftar." << endl;
        return;
    }

    tampilkanIkanHias();
    int indeks;
    cout << "Masukkan nomor ikan hias yang ingin diupdate: ";
    cin >> indeks;

    if (indeks > 0 && indeks <= jumlahIkanHias) {
        IkanHias* ikan = daftarIkanHias[indeks-1];
        cin.ignore();
        cout << "Masukkan nama ikan hias baru (kosongin kl nd mau ubah): ";
        string namaBaru;
        getline(cin, namaBaru);
        if (!namaBaru.empty()) {
            ikan->nama = namaBaru;
        }

        cout << "Masukkan jenis ikan hias baru (kosongin kl nd mau ubah): ";
        string jenisBaru;
        getline(cin, jenisBaru);
        if (!jenisBaru.empty()) {
            ikan->jenisIkan = jenisBaru;
        }

        cout << "Masukkan harga ikan hias baru (ktik 0 kl nd mau ubah): ";
        double hargaBaru;
        cin >> hargaBaru;
        if (hargaBaru != 0) {
            ikan->harga = hargaBaru;
        }

        cout << "Masukkan stok ikan hias baru (ketik -1 kl nd mau ubah): ";
        int stokBaru;
        cin >> stokBaru;
        if (stokBaru != -1) {
            ikan->stok = stokBaru;
        }

        cout << "Informasi ikan hias berhasil diupdate!!!" << endl;
    } else {
        cout << "Nomor ikan hias tidak valid." << endl;
    }
}

void hapusIkanHias() {
    if (jumlahIkanHias == 0) {
        cout << "Belum ada ikan hias dalam daftar." << endl;
        return;
    }

    tampilkanIkanHias();
    int indeks;
    cout << "Masukkan nomor ikan hias yang ingin dihapus: ";
    cin >> indeks;

    if (indeks > 0 && indeks <= jumlahIkanHias) {
        delete daftarIkanHias[indeks-1];
        for (int i = indeks-1; i < jumlahIkanHias-1; i++) {
            daftarIkanHias[i] = daftarIkanHias[i+1];
        }
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
        IkanHias* ikan = daftarIkanHias[indeks-1];
        if (jumlah > 0 && jumlah <= ikan->stok) {
            double totalHarga = ikan->harga * jumlah;
            ikan->stok -= jumlah;
            
            cout << "Pembelian berhasil!" << endl;
            cout << "Total harga: " << fixed << setprecision(2) << totalHarga << endl;

            // Menambahkan ke riwayat transaksi
            riwayatTransaksi.push_back({ikan->nama, jumlah, totalHarga, true});
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
        IkanHias* ikan = daftarIkanHias[indeks-1];
        if (jumlah > 0) {
            double totalHarga = ikan->harga * jumlah;
            ikan->stok += jumlah;
            
            cout << "Penjualan berhasil!" << endl;
            cout << "Total harga: " << fixed << setprecision(2) << totalHarga << endl;

            // Menambahkan ke riwayat transaksi
            riwayatTransaksi.push_back({ikan->nama, jumlah, totalHarga, false});
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