#include <iostream>
#include <cstdlib>  // rand(), srand()
#include <ctime>    // time()
using namespace std;

void bubblesort(int* array, int groesse)
{
    // Äußere Schleife: Nach jedem Durchlauf steht ein weiteres
    // Element an seinem endgültigen Platz am Ende.
    // Höchstens groesse-1 Durchläufe sind nötig.
    for (int i = 0; i < groesse - 1; i++)
    {
        // Innere Schleife: vergleicht benachbarte Paare.
        // Die letzten i Elemente sind schon sortiert und
        // müssen nicht mehr betrachtet werden.
        for (int j = 0; j < groesse - 1 - i; j++)
        {
            // Steht das linke Element über dem rechten -> tauschen
            if (array[j] > array[j + 1])
            {
                int hilf = array[j];       // linkes Element zwischenspeichern
                array[j] = array[j + 1];   // rechtes nach links
                array[j + 1] = hilf;       // altes linkes nach rechts
            }
        }
    }
}

int main()
{
    const int groesse = 32;

    // Zufallszahlengenerator initialisieren; die aktuelle Zeit
    // als Startwert sorgt für bei jedem Programmstart andere Zahlen.
    srand(time(0));

    // Dynamische Speicherverwaltung: "new" legt das Array auf dem
    // Heap an. Wir bekommen einen Zeiger auf das erste Element.
    int* array = new int[groesse];

    // Mit Zufallszahlen von 0 bis 99 füllen
    for (int i = 0; i < groesse; i++)
        array[i] = rand() % 100;

    // Ausgabe vor dem Sortieren
    cout << "Vorher:  ";
    for (int i = 0; i < groesse; i++)
        cout << array[i] << " ";
    cout << endl;

    // Sortieren mit der Funktion aus a)
    bubblesort(array, groesse);

    // Ausgabe nach dem Sortieren
    cout << "Nachher: ";
    for (int i = 0; i < groesse; i++)
        cout << array[i] << " ";
    cout << endl;

    // Heap-Speicher wieder freigeben (bei new[] mit delete[]),
    // sonst entsteht ein Speicherleck.
    delete[] array;

    return 0;
}

// ---------------------------------------------------------------
// c) Gedanken zur Effizienz
// - Bei n Elementen werden etwa n*(n-1)/2 Vergleiche gemacht.
//   Die Laufzeit wächst daher quadratisch: O(n^2)
//   (im besten, durchschnittlichen und schlechtesten Fall, da
//   unsere Version immer alle Durchläufe macht).
// - Verdoppelt man die Anzahl der Elemente, vervierfacht sich
//   ungefähr die Arbeit. Für 32 Zahlen ist das egal, für
//   Millionen von Zahlen aber viel zu langsam.
// - Verbesserung: Wird in einem Durchlauf nichts getauscht, ist
//   das Array sortiert und man kann abbrechen. Dann ist der
//   beste Fall (schon sortiert) nur O(n).
// - Schnellere Algorithmen wie Quicksort oder Mergesort
//   brauchen im Schnitt nur O(n log n).
// - Vorteile von Bubblesort: sehr einfach, braucht keinen
//   zusätzlichen Speicher (in-place) und ist stabil (gleiche
//   Elemente behalten ihre Reihenfolge).
// ---------------------------------------------------------------
