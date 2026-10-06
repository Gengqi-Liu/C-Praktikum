#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void bubbleSort(int* array, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main()
{
    const int SIZE = 32;

    // Array auf dem Heap anlegen
    int* array = new int[SIZE];

    // Zufallsgenerator initialisieren
    srand(time(nullptr));

    // Array mit Zufallszahlen fuellen
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = rand() % 101;
    }

    // Unsortiertes Array ausgeben
    cout << "Unsortiertes Array:" << endl;

    for (int i = 0; i < SIZE; i++)
    {
        std::cout << array[i] << " ";
    }

    std::cout << std::endl;

    // Array sortieren
    bubbleSort(array, SIZE);

    // Sortiertes Array ausgeben
    std::cout << "Sortiertes Array:" << std::endl;

    for (int i = 0; i < SIZE; i++)
    {
        std::cout << array[i] << " ";
    }

    std::cout << std::endl;

    // Dynamischen Speicher freigeben
    delete[] array;

    return 0;
}