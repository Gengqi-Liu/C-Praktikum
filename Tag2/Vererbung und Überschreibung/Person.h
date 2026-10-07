#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person
{
private:
    std::string m_sName;
    std::string m_sSurname;
    int m_iAge;

public:
    Person(std::string sName, std::string sSurname, int iAge);

    virtual ~Person();

    virtual std::string getName();

    std::string getSurname();
    int getAge();
    bool setAge(int iAge);
};

#endif