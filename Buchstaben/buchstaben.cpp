#include <iostream>
#include <string>
using namespace std;

// a) Vertauscht benachbarte Buchstaben paarweise.
// Der erste und der letzte Buchstabe bleiben stehen (Beispiel -> Biepseil).
string vertauscheBuchstaben(string wort)
{
    for (int i = 1; i + 1 < wort.size() - 1; i += 2)
    {
        char temp = wort[i];
        wort[i] = wort[i + 1];
        wort[i + 1] = temp;
    }
    return wort;
}

// b) Entfernt alle Vokale aus dem Wort.
string entferneVokale(string wort)
{
    string vokale = "aeiouAEIOU";

    // Rueckwaerts durchlaufen, damit das Loeschen die Positionen nicht stoert
    for (int i = wort.size() - 1; i >= 0; i--)
    {
        if (vokale.find(wort[i]) != string::npos)
        {
            wort.erase(i, 1);
        }
    }
    return wort;
}

// c) Woerter einlesen und beide Varianten ausgeben
int main()
{
    string wort;

    cout << "Wort eingeben (Strg+D zum Beenden): ";
    while (cin >> wort)
    {
        cout << "Vertauscht:  " << vertauscheBuchstaben(wort) << endl;
        cout << "Ohne Vokale: " << entferneVokale(wort) << endl;
        cout << "Naechstes Wort: ";
    }

    return 0;
}
