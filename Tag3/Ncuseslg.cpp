#include <iostream>
#include <list>
#include "ncurses.h"

int main()
{
// Create a list to store the characters entered by the user
    std::list<char> zeichenListe;

// Initialize ncurses
    initscr();
    nodelay(stdscr, TRUE);   
    noecho();                 

    int input;

    do
    {
        input = getch();

        if (input != -1 && input != 'q')
        {
            // Add the character to the list
            zeichenListe.push_back(static_cast<char>(input));
            // Clear the screen 
            clear();
            // Display the entered character
            printw("Eingabe ist: %c", static_cast<char>(input));
        }

    } while (input != 'q');

    endwin();

    std::cout << "Liste von hinten nach vorne: ";
    std::cout << std::endl;

    std::list<char>::reverse_iterator iterator;

    for (iterator = zeichenListe.rbegin();
         iterator != zeichenListe.rend();
         iterator++)
    {
        std::cout << *iterator;
    }

    std::cout << std::endl;

    return 0;
}