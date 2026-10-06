#include <iostream>
using namespace std;

int main() {
    int zahl;
    cout << "Bitte eine Zahl im Zehnersystem eingeben: ";
    cin >> zahl;

    if (zahl == 0) {
        cout << 0 << endl;
        return 0;
    }

    cout << "Maya-Zahl (von unten nach oben lesen):" << endl;

    while (zahl > 0) {
        int ziffer = zahl % 20;
        cout << ziffer << endl;

        zahl = zahl / 20;
    }

    return 0;
}
