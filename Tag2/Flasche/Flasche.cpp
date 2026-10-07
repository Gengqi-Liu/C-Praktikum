#include "Flasche.h"
#include <iostream>

// Standardkonstruktor
Flasche::Flasche()
    : dVolumen(0.0), sMaterial("")
{
}

// get-Methode für Volumen
double Flasche::getVolumen()
{
    return dVolumen;
}

// get-Methode für Material
std::string Flasche::getMaterial()
{
    return sMaterial;
}

// set-Methode für Volumen
void Flasche::setVolumen(double dVolumen)
{
    this->dVolumen = dVolumen;
}

// set-Methode für Material
void Flasche::setMaterial(std::string sMaterial)
{
    this->sMaterial = sMaterial;
}

// Ausgabe der Attribute
void Flasche::printFlasche()
{
    std::cout << "Volumen: " << dVolumen << std::endl;
    std::cout << "Material: " << sMaterial << std::endl;
}

// Attribute einer anderen Flasche übernehmen
void Flasche::adoptFlasche(Flasche flasche2)
{
    dVolumen = flasche2.getVolumen();
    sMaterial = flasche2.getMaterial();
}