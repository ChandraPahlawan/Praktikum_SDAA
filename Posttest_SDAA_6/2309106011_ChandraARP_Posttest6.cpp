#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>   // Untuk sqrt pada Jump Search

#include <windows.h>
using namespace std;

// Fungsi untuk membersihkan layar
void bersihkanLayar() {
    system("cls");
}

// Struktur untuk ikan hias
struct IkanHias {
    string nama;
    double harga;
    int stok;
    string jenisIkan;
    IkanHias* next;

    IkanHias(string n, double h, int s, string j) : nama(n), harga(h), stok(s), jenisIkan(j), next(nullptr) {}
};

// Linked list nyimpan ikan hias
IkanHias* head = nullptr;
int jumlahIkanHias = 0;

// Stack nyimpan riwayat penambahan ikan
stack<IkanHias*> riwayatPenambahan;

// Queue nyimpan pesanan ikan
queue<IkanHias*> antrianPesanan;

// Struktur riwayat transaksi
struct Transaksi {
    string namaIkan;
    int jumlah;
    double totalHarga;
    bool isPembelian;
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
void tampilkanRiwayatPenambahan();
void tampilkanAntrianPesanan();
void tambahPesanan();
void prosesPesanan();
void tampilkanMenu();
void tunggu();
void searchByPrice();
void searchByStock();
void searchByName();


void mergeSort(IkanHias** headRef);
IkanHias* sortedMerge(IkanHias* a, IkanHias* b);
void splitList(IkanHias* source, IkanHias** frontRef, IkanHias** backRef);

void quickSort(IkanHias** headRef);
IkanHias* getTail(IkanHias* cur);
IkanHias* partition(IkanHias* head, IkanHias* end, IkanHias** newHead, IkanHias** newEnd);
IkanHias* quickSortRecur(IkanHias* head, IkanHias* end);

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
                tampilkanRiwayatPenambahan();
                break;
            case 9:
                tampilkanAntrianPesanan();
                break;
            case 10:
                tambahPesanan();
                break;
            case 11:
                prosesPesanan();
                break;
            case 12:
                cout << "Mengurutkan harga ikan secara ascending menggunakan Merge Sort..." << endl;
                mergeSort(&head);
                tampilkanIkanHias();
                break;
            case 13:
                cout << "Mengurutkan harga ikan secara descending menggunakan Quick Sort..." << endl;
                quickSort(&head);
                tampilkanIkanHias();
                break;
            case 14:
                
                searchByPrice();
                break;
            case 15:
                tampilkanIkanHias();
                searchByStock();
                break;
            case 16:
                tampilkanIkanHias();
                 searchByName();
                break;
            case 17:
                cout << "Terima kasih telah menggunakan Sistem Jual Beli Ikan Hias!" << endl;
                 break;
            default:
                 cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                // cout << "Terima kasih telah menggunakan Sistem Jual Beli Ikan Hias!" << endl;
                break;
        }
        if (pilihan != 14) tunggu();
    } while (pilihan != 14);

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
    cout << "8. Tampilkan Riwayat Penambahan (Stack)" << endl;
    cout << "9. Tampilkan Antrian Pesanan (Queue)" << endl;
    cout << "10. Tambah Pesanan" << endl;
    cout << "11. Proses Pesanan" << endl;
    cout << "12. Urutkan Harga Ikan Ascending (Merge Sort)" << endl;
    cout << "13. Urutkan Harga Ikan Descending (Quick Sort)" << endl;
    cout << "14. Cari Ikan berdasarkan Harga (Fibonacci Search)" << endl;
    cout << "15. Cari Ikan berdasarkan Stok (Jump Search)" << endl;
    cout << "16. Cari Ikan berdasarkan Nama (Boyer-Moore)" << endl;
    cout << "17. Keluar" << endl;
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

    IkanHias* ikanBaru = new IkanHias(nama, harga, stok, jenisIkan);
    
    if (head == nullptr) {
        head = ikanBaru;
    } else {
        IkanHias* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = ikanBaru;
    }
    
    jumlahIkanHias++;
    riwayatPenambahan.push(ikanBaru);
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

// Merge Sort (Ascending)
void mergeSort(IkanHias** headRef) {
    IkanHias* head = *headRef;
    if ((head == nullptr) || (head->next == nullptr)) {
        return;
    }

    IkanHias* a;
    IkanHias* b;

    splitList(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *headRef = sortedMerge(a, b);
}

IkanHias* sortedMerge(IkanHias* a, IkanHias* b) {
    IkanHias* result = nullptr;

    if (a == nullptr)
        return b;
    else if (b == nullptr)
        return a;

    if (a->harga <= b->harga) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }

    return result;
}

void splitList(IkanHias* source, IkanHias** frontRef, IkanHias** backRef) {
    IkanHias* fast;
    IkanHias* slow;
    slow = source;
    fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

// Quick Sort (Descending)
void quickSort(IkanHias** headRef) {
    *headRef = quickSortRecur(*headRef, getTail(*headRef));
}

IkanHias* getTail(IkanHias* cur) {
    while (cur != nullptr && cur->next != nullptr)
        cur = cur->next;
    return cur;
}

IkanHias* partition(IkanHias* head, IkanHias* end, IkanHias** newHead, IkanHias** newEnd) {
    IkanHias* pivot = end;
    IkanHias* prev = nullptr, *cur = head, *tail = pivot;

    while (cur != pivot) {
        if (cur->harga >= pivot->harga) {
            if (*newHead == nullptr)
                *newHead = cur;

            prev = cur;
            cur = cur->next;
        } else {
            if (prev)
                prev->next = cur->next;

            IkanHias* temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if (*newHead == nullptr)
        *newHead = pivot;

    *newEnd = tail;

    return pivot;
}

IkanHias* quickSortRecur(IkanHias* head, IkanHias* end) {
    if (!head || head == end)
        return head;

    IkanHias* newHead = nullptr, *newEnd = nullptr;

    IkanHias* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        IkanHias* temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = nullptr;

        newHead = quickSortRecur(newHead, temp);
        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

void tunggu() {
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
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
        cout << "Masukkan nama ikan hias baru (biarkan kosong jika tidak ingin mengubah): ";
        string namaBaru;
        getline(cin, namaBaru);
        if (!namaBaru.empty()) {
            current->nama = namaBaru;
        }

        cout << "Masukkan jenis ikan hias baru (biarkan kosong jika tidak ingin mengubah): ";
        string jenisBaru;
        getline(cin, jenisBaru);
        if (!jenisBaru.empty()) {
            current->jenisIkan = jenisBaru;
        }

        cout << "Masukkan harga ikan hias baru (ketik 0 jika tidak ingin mengubah): ";
        double hargaBaru;
        cin >> hargaBaru;
        if (hargaBaru != 0) {
            current->harga = hargaBaru;
        }

        cout << "Masukkan stok ikan hias baru (ketik -1 jika tidak ingin mengubah): ";
        int stokBaru;
        cin >> stokBaru;
        if (stokBaru != -1) {
            current->stok = stokBaru;
        }

        cout << "Informasi ikan hias berhasil diupdate!" << endl;
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

            // Menambahkan ke riwayat transaksi
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


void tampilkanRiwayatPenambahan() {
    if (riwayatPenambahan.empty()) {
        cout << "Belum ada riwayat penambahan ikan." << endl;
        return;
    }

    cout << "===== RIWAYAT PENAMBAHAN IKAN HIAS =====" << endl;
    cout << setw(5) << "No" << setw(20) << "Nama" << setw(20) << "Jenis" << setw(15) << "Harga" << setw(10) << "Stok" << endl;
    
    stack<IkanHias*> tempStack = riwayatPenambahan;
    int index = 1;
    while (!tempStack.empty()) {
        IkanHias* ikan = tempStack.top();
        cout << setw(5) << index << setw(20) << ikan->nama 
             << setw(20) << ikan->jenisIkan
             << setw(15) << fixed << setprecision(2) << ikan->harga 
             << setw(10) << ikan->stok << endl;
        tempStack.pop();
        index++;
    }
}

void tampilkanAntrianPesanan() {
    if (antrianPesanan.empty()) {
        cout << "Belum ada pesanan dalam antrian." << endl;
        return;
    }

    cout << "===== ANTRIAN PESANAN IKAN HIAS =====" << endl;
    cout << setw(5) << "No" << setw(20) << "Nama" << setw(20) << "Jenis" << setw(15) << "Harga" << setw(10) << "Jumlah" << endl;
    
    queue<IkanHias*> tempQueue = antrianPesanan;
    int index = 1;
    while (!tempQueue.empty()) {
        IkanHias* ikan = tempQueue.front();
        cout << setw(5) << index << setw(20) << ikan->nama 
             << setw(20) << ikan->jenisIkan
             << setw(15) << fixed << setprecision(2) << ikan->harga 
             << setw(10) << ikan->stok << endl;
        tempQueue.pop();
        index++;
    }
}

void tambahPesanan() {
    tampilkanIkanHias();
    int indeks, jumlah;
    cout << "Masukkan nomor ikan hias yang ingin dipesan: ";
    cin >> indeks;
    cout << "Masukkan jumlah yang ingin dipesan: ";
    cin >> jumlah;

    if (indeks > 0 && indeks <= jumlahIkanHias) {
        IkanHias* current = head;
        for (int i = 1; i < indeks; i++) {
            current = current->next;
        }

        if (jumlah > 0 && jumlah <= current->stok) {
            IkanHias* pesanan = new IkanHias(current->nama, current->harga, jumlah, current->jenisIkan);
            antrianPesanan.push(pesanan);
            cout << "Pesanan berhasil ditambahkan ke antrian!" << endl;
        } else {
            cout << "Jumlah pesanan tidak valid atau stok tidak mencukupi." << endl;
        }
    } else {
        cout << "Nomor ikan hias tidak valid." << endl;
    }
}

void prosesPesanan() {
    if (antrianPesanan.empty()) {
        cout << "Tidak ada pesanan dalam antrian." << endl;
        return;
    }

    IkanHias* pesanan = antrianPesanan.front();
    antrianPesanan.pop();

    cout << "Memproses pesanan: " << pesanan->nama << " (Jumlah: " << pesanan->stok << ")" << endl;

    // Mengurangi stok ikan yang ada
    IkanHias* current = head;
    while (current != nullptr) {
        if (current->nama == pesanan->nama) {
            if (current->stok >= pesanan->stok) {
                current->stok -= pesanan->stok;
                cout << "Pesanan berhasil diproses!" << endl;
                // Menambahkan ke riwayat transaksi
                riwayatTransaksi.push_back({pesanan->nama, pesanan->stok, pesanan->harga * pesanan->stok, true});
            } else {
                cout << "Stok tidak mencukupi untuk memproses pesanan." << endl;
            }
            break;
        }
        current = current->next;
    }

    delete pesanan;
}

// Fibonacci Search 
int fibonacciSearch(IkanHias* head, double target) {
    if (head == nullptr) return -1;
    
   
    int fibM2 = 0;   // (m-2)'th Fibonacci number
    int fibM1 = 1;   // (m-1)'th Fibonacci number
    int fibM = fibM2 + fibM1;  // m'th Fibonacci number
    
    int length = 0;
    IkanHias* current = head;
    while (current != nullptr) {
        length++;
        current = current->next;
    }
    
    while (fibM < length) {
        fibM2 = fibM1;
        fibM1 = fibM;
        fibM = fibM2 + fibM1;
    }
    
    int offset = -1;
    current = head;
    
    while (fibM > 1) {
        IkanHias* temp = head;
        int i;
        for (i = 0; i <= offset + fibM2 && temp != nullptr; i++) {
            temp = temp->next;
        }
        
        if (temp == nullptr) {
            fibM = fibM1;
            fibM1 = fibM2;
            fibM2 = fibM - fibM1;
            continue;
        }
        
        if (temp->harga < target) {
            fibM = fibM1;
            fibM1 = fibM2;
            fibM2 = fibM - fibM1;
            offset = i - 1;
        }
        else if (temp->harga > target) {
            fibM = fibM2;
            fibM1 = fibM1 - fibM2;
            fibM2 = fibM - fibM1;
        }
        else {
            return i;
        }
    }
    
    return -1;
}

// Jump Search 
int jumpSearch(IkanHias* head, int target) {
    if (head == nullptr) return -1;
    
    
    int length = 0;
    IkanHias* current = head;
    while (current != nullptr) {
        length++;
        current = current->next;
    }
    
  
    int step = sqrt(length);
    int prev = 0;
    
   
    current = head;
    for (int i = 0; i < min(step, length) && current != nullptr; i++) {
        current = current->next;
    }
    
    IkanHias* prev_node = head;
    while (current != nullptr) {
        if (prev_node->stok == target) {
            return prev;
        }
        
        prev += step;
        for (int i = 0; i < step && current != nullptr; i++) {
            prev_node = current;
            current = current->next;
        }
    }
    
    
    current = prev_node;
    while (current != nullptr) {
        if (current->stok == target) {
            return prev;
        }
        current = current->next;
        prev++;
    }
    
    return -1;
}

// Boyer-Moore Search 
int boyerMooreSearch(IkanHias* head, const string& pattern) {
    const int NO_OF_CHARS = 256;
    vector<int> badChar(NO_OF_CHARS, -1);
    
   
    for (int i = 0; i < pattern.size(); i++) {
        badChar[pattern[i]] = i;
    }
    
    int index = 0;
    IkanHias* current = head;
    while (current != nullptr) {
        string text = current->nama;
        int m = pattern.length();
        int n = text.length();
        
        int s = 0;
        while (s <= (n - m)) {
            int j = m - 1;
            
            while (j >= 0 && pattern[j] == text[s + j]) {
                j--;
            }
            
            if (j < 0) {
                return index;
            } else {
                s += max(1, j - badChar[text[s + j]]);
            }
        }
        
        current = current->next;
        index++;
    }
    
    return -1;
}


void searchByPrice() {
    if (head == nullptr) {
        cout << "Belum ada ikan hias dalam daftar." << endl;
        return;
    }
    
    double targetPrice;
    cout << "Masukkan harga ikan yang ingin dicari: ";
    cin >> targetPrice;
    
    int result = fibonacciSearch(head, targetPrice);
    if (result != -1) {
        cout << "Ikan dengan harga " << targetPrice << " ditemukan pada posisi " << result + 1 << endl;
        
        
        IkanHias* current = head;
        for (int i = 0; i < result; i++) {
            current = current->next;
        }
        cout << "\nDetail Ikan:" << endl;
        cout << "Nama: " << current->nama << endl;
        cout << "Jenis: " << current->jenisIkan << endl;
        cout << "Harga: " << current->harga << endl;
        cout << "Stok: " << current->stok << endl;
    } else {
        cout << "Ikan dengan harga " << targetPrice << " tidak ditemukan." << endl;
    }
}


void searchByStock() {
    if (head == nullptr) {
        cout << "Belum ada ikan hias dalam daftar." << endl;
        return;
    }
    
    int targetStock;
    cout << "Masukkan jumlah stok ikan yang ingin dicari: ";
    cin >> targetStock;
    
    int result = jumpSearch(head, targetStock);
    if (result != -1) {
        cout << "Ikan dengan stok " << targetStock << " ditemukan pada posisi " << result + 1 << endl;
        
       
        IkanHias* current = head;
        for (int i = 0; i < result; i++) {
            current = current->next;
        }
        cout << "\nDetail Ikan:" << endl;
        cout << "Nama: " << current->nama << endl;
        cout << "Jenis: " << current->jenisIkan << endl;
        cout << "Harga: " << current->harga << endl;
        cout << "Stok: " << current->stok << endl;
    } else {
        cout << "Ikan dengan stok " << targetStock << " tidak ditemukan." << endl;
    }
}


void searchByName() {
    if (head == nullptr) {
        cout << "Belum ada ikan hias dalam daftar." << endl;
        return;
    }
    
    string targetName;
    cin.ignore();
    cout << "Masukkan nama ikan yang ingin dicari: ";
    getline(cin, targetName);
    
    int result = boyerMooreSearch(head, targetName);
    if (result != -1) {
        cout << "Ikan dengan nama " << targetName << " ditemukan pada posisi " << result + 1 << endl;
        
        
        IkanHias* current = head;
        for (int i = 0; i < result; i++) {
            current = current->next;
        }
        cout << "\nDetail Ikan:" << endl;
        cout << "Nama: " << current->nama << endl;
        cout << "Jenis: " << current->jenisIkan << endl;
        cout << "Harga: " << current->harga << endl;
        cout << "Stok: " << current->stok << endl;
    } else {
        cout << "Ikan dengan nama " << targetName << " tidak ditemukan." << endl;
    }
}