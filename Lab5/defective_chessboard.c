#include <stdio.h>
#include <stdlib.h>

int len, drow, dcol;
int *board;

void reset()
{
    printf("\033[0m");
}
void red()
{
    printf("\033[1;31m");
}

void green()
{
    printf("\033[1;32m");
}

void yellow()
{
    printf("\033[1;33m");
}

void blue()
{
    printf("\033[1;34m");
}

void white()
{
    printf("\033[1;37m");
}

void colour(int n)
{
    switch (n)
    {
    
    case 0:
        reset();
        break;
    
    case 1:
        red();
        break;
    
    case 2:
        green();
        break;
    
    case 3:
        yellow();
        break;

    case 4:
        blue();
        break;

    case 5:
        white();
        break;

    default:
        break;
    }
}

void boardFill(int defRow, int defCol, int row , int col , int size, int tileNum)
{
    if(size == 1)
        return;
    
    tileNum++;

    if(drow < row + size/2 && dcol < col + size/2)
        boardFill(defRow, defCol, row , col , size / 2 , tileNum);
    else
    {
        board[(row + size/2 - 1)*len + col + size/2 - 1] = tileNum;
        //boardFill(row + size/2 -1 , col + size/2 -1 , row, col , size/2 , tileNum);
    }
    
    if(drow >= row + size/2 && dcol < col + size/2)
        boardFill(defRow , defCol , row + size/2, col , size/2 , tileNum);
    else
    {
        board[(row + size/2)*len + col + size/2 - 1] = tileNum;
        //boardFill(row + size/2, col + size/2 - 1,row + size/2, col , size/2 , tileNum);
    }

    if(drow < row + size/2 && dcol >= col + size/2)
        boardFill(defRow , defCol ,row, col + size/2 , size/2 , tileNum);
    else
    {
        board[(row + size/2 - 1)*len + col + size/2] = tileNum;
        //boardFill(row + size/2 - 1 , col + size/2 ,row, col + size/2 , size/2 , tileNum);
    }

    if(drow >= row + size/2 && dcol >= col + size/2)
        boardFill(defRow, defCol, row + size/2, col + size/2 , size/2 , tileNum);
    else
    {
        board[(row + size/2)*len + col + size/2] = tileNum;
        //boardFill(row + size/2, col + size/2, row + size/2, col + size/2 , size/2 , tileNum);
    }

}

void printBoard()
{
    for(int i = 0 ; i < len ; i++)
    {
        for(int j = 0 ; j < len ; j++)
        {
            colour(board[i*len + j]);
            printf("%d ", board[i*len + j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    len = atoi(argv[1]);
    drow = atoi(argv[2]);
    dcol = atoi(argv[3]);

    if(len == 0 || drow == 0 || dcol == 0 || drow > len || dcol > len)
    {
        printf("error");
        return 0;
    }
    
    board = (int *)malloc(sizeof(int)*len*len);
    boardFill(drow, dcol, 0 , 0 , len , 0);
    printBoard();

    return 0;
}