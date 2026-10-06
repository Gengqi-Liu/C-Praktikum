#include <iostream>

double heron_ite(double dNumber)
{
    double dResult = dNumber;

    for (int i = 0; i < 10; i++)
    {
        dResult = 0.5 * (dResult + dNumber / dResult);
    }

    return dResult;
}

int main()
{
    double dNumber = 0.0;

    std::cout << "Bitte geben Sie eine positive Zahl ein: ";
    std::cin >> dNumber;

    if (std::cin.fail() || dNumber <= 0)
    {
        std::cout << "Fehler: Bitte eine positive Zahl eingeben."
                  << std::endl;
        return 1;
    }

    double dRoot = heron_ite(dNumber);

    std::cout << "Die Quadratwurzel von "
              << dNumber
              << " ist ungefaehr "
              << dRoot
              << std::endl;

    return 0;
}