#include <iostream>
#include <cmath>
using namespace std;

// Berechnet die reellen Lösungen von a*x^2 + b*x + c = 0.
// Rückgabe: true, wenn es eine Lösung gibt, sonst false.
bool loese(double a, double b, double c, double *x1, double *x2)
{
    double d = b * b - 4 * a * c; // Diskriminante
    if (d < 0)
        return false; // keine reelle Lösung

    *x1 = (-b + sqrt(d)) / (2 * a);
    *x2 = (-b - sqrt(d)) / (2 * a);
    return true;
}

int main()
{
    double a, b, c, x1, x2;

    cout << "a, b, c eingeben: ";
    cin >> a >> b >> c;

    if (loese(a, b, c, &x1, &x2))
        cout << "x1 = " << x1 << ", x2 = " << x2 << endl;
    else
        cout << "keine Lösung" << endl;

    return 0;
}
