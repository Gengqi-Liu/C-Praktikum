#include <iostream>
using namespace std;

// a und b sind Referenzen: Sie sind keine Kopien, sondern andere Namen
// für die Variablen, die beim Aufruf übergeben werden.
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 3;
    int y = 7;

    cout << "Vorher:  x = " << x << ", y = " << y << endl;
    swap(x, y);
    cout << "Nachher: x = " << x << ", y = " << y << endl;

    return 0;
}
