#include "Date.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    // Zufallsgenerator einmal initialisieren
    srand(time(nullptr));

    // Zufällige Datumsobjekte
    Date d1;
    Date d2;

    std::cout << "=== Zufaellig erzeugte Daten ===" << std::endl;

    std::cout << "Datum 1: "
              << d1.getDay() << "."
              << d1.getMonth() << "."
              << d1.getYear() << std::endl;

    std::cout << "Datum 2: "
              << d2.getDay() << "."
              << d2.getMonth() << "."
              << d2.getYear() << std::endl;

    // Datum durch Benutzer eingeben
    int day;
    int month;
    int year;

    std::cout << std::endl;
    std::cout << "=== Eigenes Datum eingeben ===" << std::endl;

    std::cout << "Tag: ";
    std::cin >> day;

    std::cout << "Monat: ";
    std::cin >> month;

    std::cout << "Jahr: ";
    std::cin >> year;

    Date d3(day, month, year);

    std::cout << "Datum 3: "
              << d3.getDay() << "."
              << d3.getMonth() << "."
              << d3.getYear() << std::endl;

    // isEqual() testen
    std::cout << std::endl;
    std::cout << "=== Test von isEqual() ===" << std::endl;

    if(d1.isEqual(d2))
    {
        std::cout << "Datum 1 und Datum 2 sind gleich."
                  << std::endl;
    }
    else
    {
        std::cout << "Datum 1 und Datum 2 sind nicht gleich."
                  << std::endl;
    }

    // compare() testen
    std::cout << std::endl;
    std::cout << "=== Vergleich Datum 1 mit Datum 2 ==="
              << std::endl;

    int result = d1.compare(d2);

    if(result == 1)
    {
        std::cout << "Datum 1 liegt vor Datum 2."
                  << std::endl;
    }
    else if(result == -1)
    {
        std::cout << "Datum 1 liegt nach Datum 2."
                  << std::endl;
    }
    else
    {
        std::cout << "Datum 1 und Datum 2 sind gleich."
                  << std::endl;
    }

    // Benutzerdatum vergleichen
    
    std::cout << std::endl;
    std::cout << "=== Vergleich Datum 3 mit Datum 1 ==="
              << std::endl;

    result = d3.compare(d1);

    if(result == 1)
    {
        std::cout << "Datum 3 liegt vor Datum 1."
                  << std::endl;
    }
    else if(result == -1)
    {
        std::cout << "Datum 3 liegt nach Datum 1."
                  << std::endl;
    }
    else
    {
        std::cout << "Datum 3 und Datum 1 sind gleich."
                  << std::endl;
    }

    return 0;
}