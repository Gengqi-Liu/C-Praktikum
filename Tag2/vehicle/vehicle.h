#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class vehicle
{
public:
    enum color
    {
        blue,
        red,
        green,
        white,
        black
    };

private:
    color m_color;
    double m_price;
    int m_year;
    int m_number;

    static int s_nextNumber;

public:
    vehicle(color vehicleColor, double price, int year);

    std::string getColor();
    double getPrice();
    int getYear();
    int getNumber();

    static bool isOldtimer(vehicle car);
};

#endif