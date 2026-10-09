#include <iostream>

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int a ;
    int b ;

    std::cout << "Bitte geben Sie a ein: ";
    std::cin >> a;
    std::cout << "Bitte geben Sie b ein: ";
    std::cin >> b;

    std::cout << "Vor dem Tausch:" << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    swap(a, b);

    std::cout << "Nach dem Tausch:" << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    return 0;
}