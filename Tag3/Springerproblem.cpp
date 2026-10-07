#include <iostream>
#include <iomanip>

const int SIZE = 8;


bool isValid(int board[SIZE][SIZE], int x, int y)
{
    
    // 0 <= x < 8
    // 0 <= y < 8

    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
    {
        return false;
    }


   

    if (board[x][y] != 0)
    {
        return false;
    }


   
    return true;
}


bool findpath(int board[SIZE][SIZE],
              int x,
              int y,
              int step)
{
    

    if (step == SIZE * SIZE)
    {
        return true;
    }


   
    int dx[8] =
    {
         2,  2,
        -2, -2,
         1,  1,
        -1, -1
    };

    int dy[8] =
    {
         1, -1,
         1, -1,
         2, -2,
         2, -2
    };


    for (int i = 0; i < 8; i++)
    {
       
        int nextX = x + dx[i];
        int nextY = y + dy[i];


       
        if (isValid(board, nextX, nextY))
        {
            
            board[nextX][nextY] = step + 1;


            
            if (findpath(board,
                         nextX,
                         nextY,
                         step + 1))
            {
                return true;
            }


            
            board[nextX][nextY] = 0;
        }
    }


   
    return false;
}



void printBoard(int board[SIZE][SIZE])
{
    std::cout << std::endl;
    std::cout << "Gefundener Pfad:" << std::endl;
    std::cout << std::endl;


    for (int x = 0; x < SIZE; x++)
    {
        for (int y = 0; y < SIZE; y++)
        {
            
            std::cout << std::setw(3)
                      << board[x][y]
                      << " ";
        }

        std::cout << std::endl;
    }
}


int main()
{
    
    int board[SIZE][SIZE] = {0};


    int startX;
    int startY;


    
    std::cout << "Startzeile (1-8): ";
    std::cin >> startX;

    std::cout << "Startspalte (1-8): ";
    std::cin >> startY;


    
    startX--;
    startY--;


    
    if (startX < 0 || startX >= SIZE ||
        startY < 0 || startY >= SIZE)
    {
        std::cout << "Ungueltige Startposition."
                  << std::endl;

        return 0;
    }

 
    board[startX][startY] = 1;


   
    if (findpath(board, startX, startY, 1))
    {
      
        printBoard(board);
    }
    else
    {
       
        std::cout << "Kein Pfad gefunden."
                  << std::endl;
    }


    return 0;
}