#include <iostream>
using namespace std;

void pindahkanPiringan(int Total_piringan, char menara_asal, char menara_tujuan, char menara_sementara) {
    if (Total_piringan == 1) {
        cout << "Pindahkan piringan 1 dari menara " << menara_asal << " otw ke menara " << menara_tujuan << endl;
        cout << "__________________________________________________:)" << endl;
        return;
    }
    
    pindahkanPiringan(Total_piringan - 1, menara_asal, menara_sementara, menara_tujuan);

    cout << "Pindahkan piringan " << Total_piringan << " dari menara " << menara_asal << " otw ke menara " << menara_tujuan << endl;
    cout << "__________________________________________________:)" << endl;
    
    pindahkanPiringan(Total_piringan - 1, menara_sementara, menara_tujuan, menara_asal);
}

int main() {
    int Total_piringan = 3;
    cout << "Langkah-langkah untuk memindahkan " << Total_piringan << " piringan pada Menara Hanoi:" << endl;
    
    pindahkanPiringan(Total_piringan, 'A', 'C', 'B');
    
    return 0;
}