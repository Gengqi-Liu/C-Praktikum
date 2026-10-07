#include "vehicle.h"
#include <iostream>

int main()
{
    int colorInput;
    double price;
    int year;

    // Fahrzeug 1
    std::cout << "=== Fahrzeug 1 ===" << std::endl;

    std::cout << "Farbe waehlen:" << std::endl;
    std::cout << "1 - Blau" << std::endl;
    std::cout << "2 - Rot" << std::endl;
    std::cout << "3 - Gruen" << std::endl;
    std::cout << "4 - Weiss" << std::endl;
    std::cout << "5 - Schwarz" << std::endl;
    std::cout << "Auswahl: ";
    std::cin >> colorInput;

    std::cout << "Preis: ";
    std::cin >> price;

    std::cout << "Baujahr: ";
    std::cin >> year;

    vehicle::color color1;

    if(colorInput == 1)
    {
        color1 = vehicle::blue;
    }
    else if(colorInput == 2)
    {
        color1 = vehicle::red;
    }
    else if(colorInput == 3)
    {
        color1 = vehicle::green;
    }
    else if(colorInput == 4)
    {
        color1 = vehicle::white;
    }
    else
    {
        color1 = vehicle::black;
    }

    vehicle car1(color1, price, year);


    // Fahrzeug 2
    std::cout << std::endl;
    std::cout << "=== Fahrzeug 2 ===" << std::endl;

    std::cout << "Farbe waehlen:" << std::endl;
    std::cout << "1 - Blau" << std::endl;
    std::cout << "2 - Rot" << std::endl;
    std::cout << "3 - Gruen" << std::endl;
    std::cout << "4 - Weiss" << std::endl;
    std::cout << "5 - Schwarz" << std::endl;
    std::cout << "Auswahl: ";
    std::cin >> colorInput;

    std::cout << "Preis: ";
    std::cin >> price;

    std::cout << "Baujahr: ";
    std::cin >> year;

    vehicle::color color2;

    if(colorInput == 1)
    {
        color2 = vehicle::blue;
    }
    else if(colorInput == 2)
    {
        color2 = vehicle::red;
    }
    else if(colorInput == 3)
    {
        color2 = vehicle::green;
    }
    else if(colorInput == 4)
    {
        color2 = vehicle::white;
    }
    else
    {
        color2 = vehicle::black;
    }

    vehicle car2(color2, price, year);


    // Fahrzeugdaten ausgeben
    std::cout << std::endl;
    std::cout << "=== Fahrzeugdaten ===" << std::endl;

    std::cout << std::endl;
    std::cout << "Fahrzeug 1:" << std::endl;
    std::cout << "Nummer: " << car1.getNumber() << std::endl;
    std::cout << "Farbe: " << car1.getColor() << std::endl;
    std::cout << "Preis: " << car1.getPrice() << std::endl;
    std::cout << "Baujahr: " << car1.getYear() << std::endl;

    std::cout << std::endl;
    std::cout << "Fahrzeug 2:" << std::endl;
    std::cout << "Nummer: " << car2.getNumber() << std::endl;
    std::cout << "Farbe: " << car2.getColor() << std::endl;
    std::cout << "Preis: " << car2.getPrice() << std::endl;
    std::cout << "Baujahr: " << car2.getYear() << std::endl;


  
    // isOldtimer() testen
   
    std::cout << std::endl;
    std::cout << "=== Oldtimer-Test ===" << std::endl;

    if(vehicle::isOldtimer(car1))
    {
        std::cout << "Fahrzeug 1 ist ein Oldtimer." << std::endl;
    }
    else
    {
        std::cout << "Fahrzeug 1 ist kein Oldtimer." << std::endl;
    }

    if(vehicle::isOldtimer(car2))
    {
        std::cout << "Fahrzeug 2 ist ein Oldtimer." << std::endl;
    }
    else
    {
        std::cout << "Fahrzeug 2 ist kein Oldtimer." << std::endl;
    }

    return 0;
}