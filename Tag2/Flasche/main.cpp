#include "Flasche.h"
#include <iostream>
#include <string>

int main()
{
    Flasche flasche1;
    Flasche flasche2;

    double volumen;
    std::string material;


    // Flasche 1 setzen

    std::cout << "=== Flasche 1 ===" << std::endl;

    std::cout << "Volumen eingeben: ";
    std::cin >> volumen;

    std::cout << "Material eingeben: ";
    std::cin >> material;

    flasche1.setVolumen(volumen);
    flasche1.setMaterial(material);

    
    // Flasche 2 setzen
    
    std::cout << std::endl;
    std::cout << "=== Flasche 2 ===" << std::endl;

    std::cout << "Volumen eingeben: ";
    std::cin >> volumen;

    std::cout << "Material eingeben: ";
    std::cin >> material;

    flasche2.setVolumen(volumen);
    flasche2.setMaterial(material);

    // get-Methoden testen
    std::cout << std::endl;
    std::cout << "=== Test der get-Methoden ===" << std::endl;

    std::cout << "Flasche 1:" << std::endl;
    std::cout << "Volumen: " << flasche1.getVolumen() << std::endl;
    std::cout << "Material: " << flasche1.getMaterial() << std::endl;

    std::cout << std::endl;

    std::cout << "Flasche 2:" << std::endl;
    std::cout << "Volumen: " << flasche2.getVolumen() << std::endl;
    std::cout << "Material: " << flasche2.getMaterial() << std::endl;

    // printFlasche() testen
    std::cout << std::endl;
    std::cout << "=== Test von printFlasche() ===" << std::endl;

    std::cout << "Flasche 1:" << std::endl;
    flasche1.printFlasche();

    std::cout << std::endl;

    std::cout << "Flasche 2:" << std::endl;
    flasche2.printFlasche();

    // adoptFlasche() testen
    std::cout << std::endl;
    std::cout << "Flasche 1 übernimmt jetzt die Eigenschaften von Flasche 2."
              << std::endl;

    flasche1.adoptFlasche(flasche2);

    std::cout << std::endl;
    std::cout << "Flasche 1 nach adoptFlasche():" << std::endl;
    flasche1.printFlasche();

    return 0;
}