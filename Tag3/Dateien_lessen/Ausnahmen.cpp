#include <iostream>
#include <fstream>
#include <string>
#include <exception>



class nofileException : public std::exception
{
public:

    
    virtual const char* what() const throw()
    {
        
        return "Die Datei existiert nicht";
    }
};


nofileException nofile;



void read_file(std::string Dateiname)
{
    std::ifstream datei;


    datei.open(Dateiname);


    if (datei.fail())
    {

        throw nofile;
    }



    std::string zeile;

    while (std::getline(datei, zeile))
    {
        std::cout << zeile << std::endl;
    }

    datei.close();
}



int main()
{
    std::string Dateiname;


    

    std::cout << "Bitte Dateinamen eingeben: ";
    std::getline(std::cin, Dateiname);


    

    try
    {
        read_file(Dateiname);
    }


    

    catch (const std::exception& e)
    {
        
        // Die Datei existiert nicht

        std::cout << e.what() << std::endl;
    }


    return 0;
}