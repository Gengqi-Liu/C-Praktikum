#include "square.h"

// Konstruktor
square::square(double length)
    : m_length(length)
{
}


// Kopierkonstruktor
square::square(const square& other)
    : m_length(other.m_length)
{
}


// Kantenlänge
double square::getLength() const
{
    return m_length;
}


// Fläche
double square::getArea() const
{
    return m_length * m_length;
}


// Umfang
double square::getPerimeter() const
{
    return 4 * m_length;
}


// Addition zweier Quadrate
square square::operator+(const square& other) const
{
    return square(m_length + other.m_length);
}


// Subtraktion zweier Quadrate
square square::operator-(const square& other) const
{
    return square(m_length - other.m_length);
}


// Ausgabe eines Quadrats
std::ostream& operator<<(std::ostream& os, const square& s)
{
    os << "Quadrat: Kantenlaenge=" << s.getLength()
       << ", Flaeche=" << s.getArea()
       << ", Umfang=" << s.getPerimeter();

    return os;
}