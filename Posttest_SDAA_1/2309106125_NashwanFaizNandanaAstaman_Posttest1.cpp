#include <iostream>
using namespace std;

void pindahkanPiringan(int jumlahPiringan, string menaraAsal, string menaraTujuan, string menaraSementara) {
    if (jumlahPiringan == 1) {
        //Jika hanya ada satu piringan, langsung pindahkan ke menara tujuan
        cout << "Pindahkan piringan "<< jumlahPiringan <<" dari " << menaraAsal << " ke " << menaraTujuan << endl;
    } else {
        //Pindahkan n-1 piringan menara asal ke menara sementara
        pindahkanPiringan(jumlahPiringan - 1, menaraAsal, menaraSementara, menaraTujuan);

        //Pindahkan piringan terakhir menara asal ke menara tujuan
        cout << "Pindahkan piringan "<< jumlahPiringan <<" dari " << menaraAsal << " ke " << menaraTujuan << endl;

        //Pindahkan n-1 piringan menara sementara ke menara tujuan
        pindahkanPiringan(jumlahPiringan - 1, menaraSementara, menaraTujuan, menaraAsal);
    }
}

int main() {
    int jumlahPiringan = 4  ;

    // Memulai pemindahan piringan dari menara A (asal) ke menara C (tujuan) dengan bantuan menara B (sementara)
    pindahkanPiringan(jumlahPiringan, "Menara A", "Menara C", "Menara B");

    return 0;
}
