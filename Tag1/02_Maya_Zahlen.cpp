#include <iostream>

int main()
{
    int iDecimal;

    std::cout << "Zahl im Zehnersystem: ";
    std::cin >> iDecimal;

    int digits[100];
    int count = 0;

    do
    {
        digits[count] = iDecimal % 20;
        iDecimal = iDecimal / 20;
        count++;
    }
    while (iDecimal > 0);

    std::cout << "Zahl im Zwanzigersystem: ";

    for (int i = count - 1; i >= 0; i--)
    {
        std::cout << digits[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}