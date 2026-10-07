#include <iostream>
#include "ncurses.h"


struct Node
{
    char data;

    Node* prev;

    Node* next;
};


int main()
{
    
    Node* head = nullptr;
    Node* tail = nullptr;


    
    initscr();
    nodelay(stdscr, TRUE);
    noecho();


    int input = -1;


   
    while (input != 'q')
    {
        
        input = getch();


       
        if (input != -1)
        {
            
            if (input != 'q')
            {
                
                Node* newNode = new Node;

                newNode->data = static_cast<char>(input);
                newNode->prev = tail;
                newNode->next = nullptr;


                
                if (head == nullptr)
                {
                    
                    head = newNode;
                    tail = newNode;
                }
                else
                {
                    tail->next = newNode;

                   
                    tail = newNode;
                }


                
                clear();


                
                printw("Eingabe ist: %c",
                       static_cast<char>(input));
                refresh();
            }
        }
    }


    
    endwin();


    
    std::cout << "Liste von hinten nach vorne: ";


    
    Node* current = tail;


    while (current != nullptr)
    {
        std::cout << current->data;

        
        current = current->prev;
    }


    std::cout << std::endl;


    
    current = head;

    while (current != nullptr)
    {
        Node* nextNode = current->next;

        delete current;

        current = nextNode;
    }


    return 0;
}