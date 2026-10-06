#include <iostream>
#include <limits>
using namespace std;

double zahlEinlesen(){
    double a;
    cout << "Bitte die Zahl eingeben, deren Quadratwurzel gesucht ist: ";
    
    while(true){
        if(cin >> a){
            return a;
        }

        cout << "Ungültige Eingabe. Bitte gültige Zahl eingeben: ";

        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }

    
}

double heron_ite(double a){
    
    double x = 1;

    for(int i = 0; i < 10; i++){
        x = (x + (a/x)) / 2;
    }

    return x;
}

int main(){
    double a = zahlEinlesen();
    double wurzel = heron_ite(a);

    cout << "Die Wurzel von " << a << " ist gleich " << wurzel << "." << endl;
}
