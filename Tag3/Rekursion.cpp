#include <iostream>

// ========================================
// a) Iterative Berechnung
// ========================================

unsigned long long factorialIter(unsigned int n)
{

    unsigned long long result = 1;

    // result = 1
    // result = 1 * 1 = 1
    // result = 1 * 2 = 2
    // result = 2 * 3 = 6
    // result = 6 * 4 = 24
    // result = 24 * 5 = 120

    for (unsigned int i = 1; i <= n; i++)
    {
        result = result * i;
    }

    return result;
}


// ========================================
// b) Rekursive Berechnung
// ========================================

unsigned long long factorialRec(unsigned int n)
{
    
    // 0! = 1
   
    if (n == 0)
    {
        return 1;
    }

   
    return n * factorialRec(n - 1);
}


// ========================================
// main
// ========================================

int main()
{
    unsigned int number;

   
    std::cout << "Bitte geben Sie eine Zahl ein: ";
    std::cin >> number;


    // a)  iterative Funktion
    std::cout << "Fakultaet iterativ: "
              << factorialIter(number)
              << std::endl;


    // b)  rekursive Funktion
    std::cout << "Fakultaet rekursiv: "
              << factorialRec(number)
              << std::endl;


    return 0;
}