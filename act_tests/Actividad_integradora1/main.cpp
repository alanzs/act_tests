#include <iostream>
#include <vector>
#include "analizador.h"

using namespace std;

int main() {
    string t1 = leerArchivo("transmission1.txt");
    string t2 = leerArchivo("transmission2.txt");
    vector<string> mcodes = {
        leerArchivo("mcode1.txt"),
        leerArchivo("mcode2.txt"),
        leerArchivo("mcode3.txt")
    };

    cout << "parte 1" << endl;
    for (int i = 0; i < 2; ++i) {
        const string& t = (i == 0) ? t1 : t2;
        for (int j = 0; j < 3; ++j) {
            int pos = buscarSubcadena(t, mcodes[j]);
            cout << ((pos != -1) ? "true " + to_string(pos) : "false") << endl;
        }
    }

    cout << "parte 2" << endl;
    auto [inicio1, fin1, pal1] = palindromoMasLargo(t1);
    cout << inicio1 << " " << fin1 << " " << pal1 << endl;

    auto [inicio2, fin2, pal2] = palindromoMasLargo(t2);
    cout << inicio2 << " " << fin2 << " " << pal2 << endl;

    cout << "parte 3" << endl;
    auto [start1, end1, start2, end2, substr] = lcs(t1, t2);
    cout << start1 << " " << end1 << " " << substr << endl;

    return 0;
}
