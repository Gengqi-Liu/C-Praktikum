#include <iostream>
#include <string>

// Aufgabe a)
// Tauscht jeweils zwei benachbarte Buchstaben.
// Der erste und der letzte Buchstabe bleiben unverändert.
std::string changeLetters(std::string word)
{
    for (int i = 1; i < word.size() - 2; i += 2) //Der erste und der letzte Buchstabe bleiben unveraendert.
    {
        char temp = word[i];
        word[i] = word[i + 1]; // Tauscht jeweils zwei benachbarte Buchstaben.
        word[i + 1] = temp;
    }

    return word;
}

// Aufgabe b)
// Entfernt alle Vokale aus einem Wort.
std::string removeVowels(std::string word)
{
    for (int i = 0; i < word.size(); )
    {
        if (word[i] == 'a' || word[i] == 'e' ||
            word[i] == 'i' || word[i] == 'o' ||
            word[i] == 'u' || word[i] == 'A' ||
            word[i] == 'E' || word[i] == 'I' ||
            word[i] == 'O' || word[i] == 'U')
        {
            word.erase(i, 1);
        }
        else
        {
            i++;
        }
    }

    return word;
}

int main()
{
    std::string word;

    std::cout << "Bitte geben Sie ein Wort ein: ";
    std::cin >> word;

    std::cout << "Veraenderte Buchstabenreihenfolge: "
              << changeLetters(word) << std::endl;

    std::cout << "Ohne Vokale: "
              << removeVowels(word) << std::endl;

    return 0;
}