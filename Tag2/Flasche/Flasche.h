#ifndef FLASCHE_H
#define FLASCHE_H

#include <string>

class Flasche
{
private:
    double dVolumen;
    std::string sMaterial;

public:
    // Standardkonstruktor
    Flasche();

    // get-Methoden
    double getVolumen();
    std::string getMaterial();

    // set-Methoden
    void setVolumen(double dVolumen);
    void setMaterial(std::string sMaterial);

    // Ausgabe der Attribute
    void printFlasche();

    // Attribute einer anderen Flasche übernehmen
    void adoptFlasche(Flasche flasche2);
};

#endif