#include <iostream>
#include <cmath>

bool solveQuadratic(double a, double b, double c,
                    double* solution1, double* solution2)
{
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return false;
    }

    *solution1 = (-b + std::sqrt(discriminant)) / (2 * a);
    *solution2 = (-b - std::sqrt(discriminant)) / (2 * a);

    return true;
}

int main()
{
    double a, b, c;
    double x1, x2;

    std::cout << "Bitte geben Sie a ein: ";
    std::cin >> a;

    std::cout << "Bitte geben Sie b ein: ";
    std::cin >> b;

    std::cout << "Bitte geben Sie c ein: ";
    std::cin >> c;

    if (a == 0)
    {
        std::cout << "Keine quadratische Gleichung." << std::endl;
        return 1;
    }

    bool hasSolution = solveQuadratic(a, b, c, &x1, &x2);

    if (hasSolution)
    {
        std::cout << "x1 = " << x1 << std::endl;
        std::cout << "x2 = " << x2 << std::endl;
    }
    else
    {
        std::cout << "Keine reelle Loesung." << std::endl;
    }

    return 0;
}