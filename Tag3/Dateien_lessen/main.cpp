#include <iostream>
#include <fstream>
#include <string>




void read_file(std::string Dateiname)
{
    // ifstream = input file stream
   

    std::ifstream datei(Dateiname);


    
    if (!datei.is_open())
    {
        std::cout << "Datei konnte nicht geoeffnet werden."
                  << std::endl;

        return;
    }


  

    std::string zeile;


   

    while (std::getline(datei, zeile))
    {
       
        std::cout << zeile << std::endl;
    }


    
    datei.close();
}




void write_file(std::string Dateiname)
{
    // ofstream = output file stream
    
    // app = append
    
    std::ofstream datei(Dateiname, std::ios::app);


    

    if (!datei.is_open())
    {
        std::cout << "Datei konnte nicht geoeffnet werden."
                  << std::endl;

        return;
    }


   

    std::string zeile;


    std::cout << "Text eingeben (exit zum Beenden):"
              << std::endl;


   

    while (true)
    {
        

        std::getline(std::cin, zeile);


       

        if (zeile == "exit")
        {
            break;
        }



        datei << zeile << std::endl;
    }


   

    datei.close();
}




int main()
{
    std::string Dateiname;


    
    // test.txt

    std::cout << "Bitte Dateinamen eingeben: ";
    std::getline(std::cin, Dateiname);


    
    std::cout << std::endl;
    std::cout << "Inhalt der Datei:"
              << std::endl;

    read_file(Dateiname);


    
    std::cout << std::endl;
    std::cout << "Neuen Text an die Datei anhaengen:"
              << std::endl;

    write_file(Dateiname);


   
    std::cout << std::endl;
    std::cout << "Neuer Inhalt der Datei:"
              << std::endl;

    read_file(Dateiname);


    return 0;
}