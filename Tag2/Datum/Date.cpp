#include "Date.h"
#include <cstdlib>

// Standardkonstruktor
Date::Date()
{
    // Zufälliges Jahr zwischen 1970 und 2030
    m_year = rand() % 61 + 1970;

    // Zufälliger Monat zwischen 1 und 12
    m_month = rand() % 12 + 1;

    int maxDays;

    if(m_month == 2)
    {
        maxDays = 28;
    }
    else if(m_month == 4 ||
            m_month == 6 ||
            m_month == 9 ||
            m_month == 11)
    {
        maxDays = 30;
    }
    else
    {
        maxDays = 31;
    }

    // Zufälliger gültiger Tag
    m_day = rand() % maxDays + 1;
}

// Überladener Konstruktor
Date::Date(int day, int month, int year)
{
    m_day = day;
    m_month = month;
    m_year = year;
}

int Date::getDay()
{
    return m_day;
}

int Date::getMonth()
{
    return m_month;
}

int Date::getYear()
{
    return m_year;
}

bool Date::isEqual(Date dd)
{
    if(m_day == dd.m_day &&
       m_month == dd.m_month &&
       m_year == dd.m_year)
    {
        return true;
    }

    return false;
}

int Date::compare(Date dd)
{
    if(m_year < dd.m_year)
    {
        return 1;
    }

    if(m_year > dd.m_year)
    {
        return -1;
    }

    if(m_month < dd.m_month)
    {
        return 1;
    }

    if(m_month > dd.m_month)
    {
        return -1;
    }

    if(m_day < dd.m_day)
    {
        return 1;
    }

    if(m_day > dd.m_day)
    {
        return -1;
    }

    return 0;
}