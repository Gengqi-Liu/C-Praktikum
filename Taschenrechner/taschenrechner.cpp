#include <iostream>  // Bibliothek für Ein- und Ausgabe (cin, cout)
#include <limits>    // Bibliothek für numeric_limits (wird zum Leeren des Eingabepuffers gebraucht)

using namespace std; // Damit wir "cout" statt "std::cout" schreiben können

// a) Zahl einlesen und auf Gültigkeit prüfen (Kommazahlen erlaubt, Punkt als Dezimaltrenner)
double zahlEinlesen(const string& aufforderung) { // Funktion gibt eine Kommazahl (double) zurück; bekommt den Anzeigetext übergeben
    double zahl;                                   // Variable, in der die eingegebene Zahl gespeichert wird
    while (true) {                                 // Endlosschleife: läuft, bis eine gültige Zahl eingegeben wurde
        cout << aufforderung;                      // Text anzeigen, z.B. "Erste Zahl: "
        if (cin >> zahl) {                         // Versuch, eine Zahl zu lesen; true, wenn es geklappt hat
            return zahl;                           // Gültig: Zahl zurückgeben und Funktion beenden
        }
        if (cin.eof()) {                           // Wurde die Eingabe komplett beendet (z.B. Strg+D)?
            cout << "\nEingabe beendet." << endl;  // Hinweis ausgeben
            exit(1);                               // Programm beenden (sonst Endlosschleife)
        }
        cout << "Ungueltige Eingabe! Bitte eine Zahl eingeben (Dezimaltrenner: Punkt)." << endl; // Fehlermeldung
        cin.clear();                               // Fehlerzustand von cin zurücksetzen, sonst lesen wir nichts mehr
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Falsche Eingabe bis zum Zeilenende verwerfen
    }                                              // Zurück an den Schleifenanfang -> erneut fragen
}

// b) Operator einlesen (+, -, *, /)
char operatorEinlesen() {                          // Funktion gibt ein einzelnes Zeichen (char) zurück
    char op;                                       // Variable für den Operator
    while (true) {                                 // Wiederholen, bis ein gültiger Operator eingegeben wurde
        cout << "Operator (+, -, *, /): ";         // Aufforderung anzeigen
        if (cin >> op && (op == '+' || op == '-' || op == '*' || op == '/')) { // Zeichen gelesen UND es ist eines der vier erlaubten?
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Rest der Zeile verwerfen (z.B. wenn "+abc" getippt wurde)
            return op;                             // Gültigen Operator zurückgeben
        }
        if (cin.eof()) {                           // Eingabe komplett beendet?
            cout << "\nEingabe beendet." << endl;  // Hinweis ausgeben
            exit(1);                               // Programm beenden
        }
        cout << "Ungueltiger Operator! Erlaubt sind nur +, -, * und /." << endl; // Fehlermeldung
        cin.clear();                               // Fehlerzustand zurücksetzen
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Restliche falsche Eingabe der Zeile verwerfen
    }
}

int main() {                                       // Hier startet das Programm
    cout << "=== Taschenrechner ===" << endl;      // Titel ausgeben

    double a = zahlEinlesen("Erste Zahl: ");       // Erste Zahl einlesen (mit Prüfung)
    char op = operatorEinlesen();                  // Operator einlesen (mit Prüfung)
    double b = zahlEinlesen("Zweite Zahl: ");      // Zweite Zahl einlesen (mit Prüfung)

    // Unerlaubte Operation: Division durch 0 -> zweite Zahl erneut abfragen
    while (op == '/' && b == 0) {                  // Solange geteilt werden soll und der Teiler 0 ist...
        cout << "Division durch 0 ist nicht erlaubt! Bitte eine andere zweite Zahl eingeben." << endl; // ...Fehlermeldung
        b = zahlEinlesen("Zweite Zahl: ");         // ...und neue zweite Zahl abfragen
    }

    double ergebnis;                               // Variable für das Ergebnis
    switch (op) {                                  // Je nach Operator wird ein anderer Fall ausgeführt
        case '+': ergebnis = a + b; break;         // Addition; break verlässt das switch
        case '-': ergebnis = a - b; break;         // Subtraktion
        case '*': ergebnis = a * b; break;         // Multiplikation
        default:  ergebnis = a / b; break;         // Alles andere kann nur '/' sein: Division
    }

    cout << a << " " << op << " " << b << " = " << ergebnis << endl; // Rechnung samt Ergebnis ausgeben
    return 0;                                      // 0 = Programm wurde erfolgreich beendet
}
