#include "vehicle.h"

// Initialisierung der statischen Variable
int vehicle::s_nextNumber = 0;


// Konstruktor
vehicle::vehicle(color vehicleColor, double price, int year)
{
    m_color = vehicleColor;
    m_price = price;
    m_year = year;

    s_nextNumber++;
    m_number = s_nextNumber;
}


// Farbe als string zurückgeben
std::string vehicle::getColor()
{
    if(m_color == color::blue)
    {
        return "Blau";
    }
    else if(m_color == color::red)
    {
        return "Rot";
    }
    else if(m_color == color::green)
    {
        return "Gruen";
    }
    else if(m_color == color::white)
    {
        return "Weiss";
    }
    else
    {
        return "Schwarz";
    }
}


double vehicle::getPrice()
{
    return m_price;
}


int vehicle::getYear()
{
    return m_year;
}


int vehicle::getNumber()
{
    return m_number;
}


bool vehicle::isOldtimer(vehicle car)
{
    if(car.getYear() < 1980)
    {
        return true;
    }

    return false;
}