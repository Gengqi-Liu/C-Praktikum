#include <iostream>
#include <string>

#include "Person.h"
#include "Student.h"

int main()
{
    std::string name;
    std::string surname;
    int age;
    unsigned int studentID;

    // d) Person
    std::cout << "=== Person ===" << std::endl;

    std::cout << "Name: ";
    std::cin >> name;

    std::cout << "Nachname: ";
    std::cin >> surname;

    std::cout << "Alter: ";
    std::cin >> age;

    Person person(name, surname, age);


    // d) Student
    std::cout << std::endl;
    std::cout << "=== Student ===" << std::endl;

    std::cout << "Name: ";
    std::cin >> name;

    std::cout << "Nachname: ";
    std::cin >> surname;

    std::cout << "Alter: ";
    std::cin >> age;

    std::cout << "Student-ID: ";
    std::cin >> studentID;

    Student student(name, surname, age, studentID);


    // d)  getName()
    std::cout << std::endl;
    std::cout << "=== Aufgabe d) ===" << std::endl;

    std::cout << "Person: "
              << person.getName()
              << std::endl;

    std::cout << "Student: "
              << student.getName()
              << std::endl;


    // e) new Person
    Person person2(name, surname, age);

    // Student to Person 
    person2 = student;

    std::cout << std::endl;
    std::cout << "=== Aufgabe e) ===" << std::endl;

    std::cout << "Person nach Zuweisung des Students: "<< std::endl
              << person2.getName()<<std::endl
              << person2.getSurname()<<std::endl
              << person2.getAge()<< std::endl;

// virtuelle Methoden
    Person* p1;
    Person* p2;
    Person* p3;
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