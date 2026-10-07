#include <iostream>
#include <string>

#include "Person.h"
#include "Student.h"

int main()
{
    Person* p1;
    Person* p2;
    Person* p3;

    std::string name;
    std::string surname;
    int age;
    unsigned int studentID;


    // Student 1
    std::cout << "=== Student 1 ===" << std::endl;

    std::cout << "Name: ";
    std::cin >> name;

    std::cout << "Nachname: ";
    std::cin >> surname;

    std::cout << "Alter: ";
    std::cin >> age;

    std::cout << "Student-ID: ";
    std::cin >> studentID;

    p1 = new Student(name, surname, age, studentID);


    // Student 2
    std::cout << std::endl;
    std::cout << "=== Student 2 ===" << std::endl;

    std::cout << "Name: ";
    std::cin >> name;

    std::cout << "Nachname: ";
    std::cin >> surname;

    std::cout << "Alter: ";
    std::cin >> age;

    std::cout << "Student-ID: ";
    std::cin >> studentID;

    p2 = new Student(name, surname, age, studentID);


    // Student 3
    std::cout << std::endl;
    std::cout << "=== Student 3 ===" << std::endl;

    std::cout << "Name: ";
    std::cin >> name;

    std::cout << "Nachname: ";
    std::cin >> surname;

    std::cout << "Alter: ";
    std::cin >> age;

    std::cout << "Student-ID: ";
    std::cin >> studentID;

    p3 = new Student(name, surname, age, studentID);


    // Ausgabe
    std::cout << std::endl;
    std::cout << "=== Ausgabe ===" << std::endl;

    std::cout << std::endl;
    std::cout << "Student 1:" << std::endl;
    std::cout << "Name: " << p1->getName() << std::endl;
    std::cout << "Nachname: " << p1->getSurname() << std::endl;
    std::cout << "Alter: " << p1->getAge() << std::endl;

    std::cout << std::endl;
    std::cout << "Student 2:" << std::endl;
    std::cout << "Name: " << p2->getName() << std::endl;
    std::cout << "Nachname: " << p2->getSurname() << std::endl;
    std::cout << "Alter: " << p2->getAge() << std::endl;

    std::cout << std::endl;
    std::cout << "Student 3:" << std::endl;
    std::cout << "Name: " << p3->getName() << std::endl;
    std::cout << "Nachname: " << p3->getSurname() << std::endl;
    std::cout << "Alter: " << p3->getAge() << std::endl;


    // Dynamisch erzeugten Speicher wieder freigeben
    delete p1;
    delete p2;
    delete p3;

    return 0;
}