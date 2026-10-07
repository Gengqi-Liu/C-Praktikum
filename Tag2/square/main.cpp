#include "square.h"
#include <iostream>

int main()
{
    double length1;
    double length2;

    std::cout << "Kantenlaenge des ersten Quadrats: ";
    std::cin >> length1;

    std::cout << "Kantenlaenge des zweiten Quadrats: ";
    std::cin >> length2;

    // Konstruktor testen
    square q1(length1);
    square q2(length2);

    // get-Methoden testen
    std::cout << std::endl;
    std::cout << "=== Test der get-Methoden ===" << std::endl;

    std::cout << "Quadrat 1:" << std::endl;
    std::cout << "Kantenlaenge: " << q1.getLength() << std::endl;
    std::cout << "Flaeche: " << q1.getArea() << std::endl;
    std::cout << "Umfang: " << q1.getPerimeter() << std::endl;

    std::cout << std::endl;

    std::cout << "Quadrat 2:" << std::endl;
    std::cout << "Kantenlaenge: " << q2.getLength() << std::endl;
    std::cout << "Flaeche: " << q2.getArea() << std::endl;
    std::cout << "Umfang: " << q2.getPerimeter() << std::endl;


    // Kopierkonstruktor testen
    square qCopy(q1);

    std::cout << std::endl;
    std::cout << "=== Test des Kopierkonstruktors ===" << std::endl;
    std::cout << "Kopie von Quadrat 1:" << std::endl;
    std::cout << qCopy << std::endl;


    // + Operator testen
    square qSum = q1 + q2;

    std::cout << std::endl;
    std::cout << "=== Addition ===" << std::endl;
    std::cout << q1 << std::endl;
    std::cout << "+ " << q2 << std::endl;
    std::cout << "= " << qSum << std::endl;


    // - Operator testen
    square qDifference = q1 - q2;

    std::cout << std::endl;
    std::cout << "=== Subtraktion ===" << std::endl;
    std::cout << q1 << std::endl;
    std::cout << "- " << q2 << std::endl;
    std::cout << "= " << qDifference << std::endl;

    return 0;
}