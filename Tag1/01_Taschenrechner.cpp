#include <iostream>

int main()
{
    double dNumber1 = 0.0;
    double dNumber2 = 0.0;
    char chOperator = ' ';

    // Erste Zahl einlesen
    std::cout << "Bitte geben Sie die erste Zahl ein: ";
    std::cin >> dNumber1;

    // Fehleingaben abfangen
    while (std::cin.fail())
    {
        std::cout << "Falscheingabe: Bitte eine Zahl eingeben: ";

        std::cin.clear();
        std::cin.ignore(1000, '\n');

        std::cin >> dNumber1;
    }

    // Operator einlesen
    std::cout << "Bitte geben Sie einen Operator (+, -, *, /) ein: ";
    std::cin >> chOperator;

    // Ungueltige Operatoren abfangen
    while (chOperator != '+' &&
           chOperator != '-' &&
           chOperator != '*' &&
           chOperator != '/')
    {
        std::cout << "Falscheingabe: Bitte +, -, * oder / eingeben: ";

        std::cin.clear();
        std::cin.ignore(1000, '\n');

        std::cin >> chOperator;
    }

    // Zweite Zahl einlesen
    std::cout << "Bitte geben Sie die zweite Zahl ein: ";
    std::cin >> dNumber2;

    // Fehleingaben abfangen
    while (std::cin.fail())
    {
        std::cout << "Falscheingabe: Bitte eine Zahl eingeben: ";

        std::cin.clear();
        std::cin.ignore(1000, '\n');

        std::cin >> dNumber2;
    }

    // Berechnung durchfuehren
    switch (chOperator)
    {
        case '+':
            std::cout << "Ergebnis: "
                      << dNumber1 + dNumber2
                      << std::endl;
            break;

        case '-':
            std::cout << "Ergebnis: "
                      << dNumber1 - dNumber2
                      << std::endl;
            break;

        case '*':
            std::cout << "Ergebnis: "
                      << dNumber1 * dNumber2
                      << std::endl;
            break;

        case '/':
            if (dNumber2 == 0.0)
            {
                std::cout << "Fehler: Division durch Null ist nicht erlaubt."
                          << std::endl;
            }
            else
            {
                std::cout << "Ergebnis: "
                          << dNumber1 / dNumber2
                          << std::endl;
            }
            break;
    }

    return 0;
}