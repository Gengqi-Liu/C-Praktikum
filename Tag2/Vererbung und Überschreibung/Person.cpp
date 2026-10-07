#include "Person.h"

Person::Person(std::string sName, std::string sSurname, int iAge)
    : m_sName(sName), m_sSurname(sSurname), m_iAge(iAge)
{
}

Person::~Person()
{
}

std::string Person::getName()
{
    return m_sName;
}

std::string Person::getSurname()
{
    return m_sSurname;
}

int Person::getAge()
{
    return m_iAge;
}

bool Person::setAge(int iAge)
{
    m_iAge = iAge;
    return true;
}