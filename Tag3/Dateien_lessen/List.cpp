#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>



struct coord
{
    float x;
    float y;

   
    coord(float xValue, float yValue)
    {
        x = xValue;
        y = yValue;
    }
};



void printlist(std::list<coord>* coords)
{
    
    for (std::list<coord>::iterator it = coords->begin();
         it != coords->end();
         it++)
    {
        
        std::cout << "X: " << it->x
                  << ", Y: " << it->y
                  << std::endl;
    }
}



void delcoords(std::list<coord>& coords)
{
    std::list<coord>::iterator it = coords.begin();

    while (it != coords.end())
    {
        
        if (it->x < it->y)
        {
            
            it = coords.erase(it);
        }
        else
        {
            
            it++;
        }
    }
}


int main()
{
    
    srand(time(nullptr));


    std::list<coord> coords;


    
    int number;

    std::cout << "Wie viele Koordinaten sollen erstellt werden? ";
    std::cin >> number;


    
    for (int i = 0; i < number; i++)
    {
        
        float x = (rand() % 100) / 10.0f;
        float y = (rand() % 100) / 10.0f;

        
        coords.push_back(coord(x, y));
    }


   
    std::cout << std::endl;
    std::cout << "Originale Liste:" << std::endl;

    
    printlist(&coords);


    
    //std::list<coord> backup = coords;
    std::list<coord> backup(coords);


   
    delcoords(coords);


    
    std::cout << std::endl;
    std::cout << "Liste nach delcoords:" << std::endl;

    printlist(&coords);


    
    std::cout << std::endl;
    std::cout << "Backup:" << std::endl;

    printlist(&backup);


    return 0;
}