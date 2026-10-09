#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    const int SIZE = 100000;

    // Dynamischen Speicher fÜr das Array reservieren
    int* iArray = new int[SIZE];

    // Zufallszahlengenerator initialisieren
    srand(time(nullptr));

    int iCounter = 0;

    // Array mit Zufallszahlen von 0 bis 100 fuellen
    for (int i = 0; i < SIZE; i++)
    {
        iArray[i] = rand() % 101; // Zufallszahl zwischen 0 und 100

        // Pruefen, ob die Zahl ohne Rest durch 13 teilbar ist
        if (iArray[i] % 13 == 0)
        {
            iCounter++;
        }
    }

    std::cout << "Anzahl der durch 13 teilbaren Zahlen: "
              << iCounter << std::endl;

    // Dynamisch reservierten Speicher wieder freigeben
    delete[] iArray;

    return 0;
}