#ifndef SQUARE_H

#define SQUARE_H

#include <iostream>

class square

{

private:

    const double m_length;

public:

    // Konstruktor

    square(double length);

    // Kopierkonstruktor

    square(const square& other);

    // get-Methoden

    double getLength() const;

    double getArea() const;

    double getPerimeter() const;

    // Operatorüberladung

    square operator+(const square& other) const;

    square operator-(const square& other) const;

};

// Überladung des << Operators

std::ostream& operator<<(std::ostream& os, const square& s);

#endif