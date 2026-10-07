#ifndef DATE_H
#define DATE_H

class Date
{
private:
    int m_day;
    int m_month;
    int m_year;

public:
    // Standardkonstruktor
    Date();

    // Überladener Konstruktor
    Date(int day, int month, int year);

    bool isEqual(Date dd);

    int compare(Date dd);

    int getDay();
    int getMonth();
    int getYear();
};

#endif