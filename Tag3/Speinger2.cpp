#include <iostream>
#include <iomanip>// Include the iomanip library for formatting output

const int SIZE = 8;

//  borad 二维 int 数组（zweidimensionales Array）

bool isValid(int board[SIZE][SIZE], int x, int y)
{
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
    {
        return false;
    }

    if (board[x][y] != 0)// Check if the square has already been visited
    {
        return false;
    }
    {
        return false;
    }

    return true;
}



int countMoves(int board[SIZE][SIZE], int x, int y)// Count the number of valid moves from the current position
{
    
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


    int count = 0;



    for (int i = 0; i < 8; i++)
    {
        int nextX = x + dx[i];
        int nextY = y + dy[i];

        if (isValid(board, nextX, nextY))
        {
            count++;
        }
    }


    return count;
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


   
    int possibleX[8];
    int possibleY[8];
    int possibleMoves[8];

    int numberOfPossibilities = 0;


// 第1个 for：找出“现在”所有能走的位置
//我现在这一格，下一步有哪些地方可以走；并且如果走到那些地方，各自再往下一步有多少种可能。
    for (int i = 0; i < 8; i++)
    {
        int nextX = x + dx[i];
        int nextY = y + dy[i];


        if (isValid(board, nextX, nextY))
        {
          
            possibleX[numberOfPossibilities] = nextX;
            possibleY[numberOfPossibilities] = nextY;


        
            possibleMoves[numberOfPossibilities]
                = countMoves(board, nextX, nextY);


            numberOfPossibilities++;
        }
    }

// 第2个双层 for：把这些位置按照“下一步可能性”排序
    for (int i = 0; i < numberOfPossibilities - 1; i++)
    {
        for (int j = i + 1; j < numberOfPossibilities; j++)
        {
            if (possibleMoves[j] < possibleMoves[i])
            {
              
                int tempMoves = possibleMoves[i];
                possibleMoves[i] = possibleMoves[j];
                possibleMoves[j] = tempMoves;


                
                int tempX = possibleX[i];
                possibleX[i] = possibleX[j];
                possibleX[j] = tempX;


                int tempY = possibleY[i];
                possibleY[i] = possibleY[j];
                possibleY[j] = tempY;
            }
        }
    }

// 第3个 for：按照排好的顺序，一个一个真正尝试
    for (int i = 0; i < numberOfPossibilities; i++)
    {
        int nextX = possibleX[i];
        int nextY = possibleY[i];



        board[nextX][nextY] = step + 1;


// 递归调用
        if (findpath(board,
                     nextX,
                     nextY,
                     step + 1))
        {
            return true;
        }



        board[nextX][nextY] = 0;
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


    startX--;// Adjust for 0-based indexing
    startY--;// Adjust for 0-based indexing


    // Check if the starting position is valid
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