#include <iostream>



unsigned long long fibonacci(unsigned int n)
{
   
    
    if (n == 1 || n == 2)
    {
        return 1;
    }


    
    // fn = f(n-1) + f(n-2)
    
    return fibonacci(n - 1) + fibonacci(n - 2);
}



int main()
{

    unsigned int n;

    std::cout << "Bitte geben Sie n ein: ";
    std::cin >> n;


    if (n >= 1)
    {
        std::cout << "Das " << n
                  << ". Glied der Fibonacci-Folge ist: "
                  << fibonacci(n)
                  << std::endl;
    }
    else
    {
        std::cout << "n muss mindestens 1 sein."
                  << std::endl;
    }


    
    std::cout << std::endl;
    std::cout << "Die ersten 15 Glieder der Fibonacci-Folge:"
              << std::endl;

    
    for (unsigned int i = 1; i <= 15; i++)
    {
        std::cout << fibonacci(i) << " ";
    }

    std::cout << std::endl;


    return 0;
}