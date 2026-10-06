#include <iostream>
#include <string>

bool isPalindrome(std::string strWord)
{
    for (int i = 0; i < strWord.size() / 2; i++)
    {
        if (strWord[i] != strWord[strWord.size() - 1 - i])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    std::string strWord;

    std::cout << "Bitte geben Sie ein Wort in Kleinbuchstaben ein: ";
    std::cin >> strWord;

    if (isPalindrome(strWord))
    {
        std::cout << strWord << " ist ein Palindrom." << std::endl;
    }
    else
    {
        std::cout << strWord << " ist kein Palindrom." << std::endl;
    }

    return 0;
}