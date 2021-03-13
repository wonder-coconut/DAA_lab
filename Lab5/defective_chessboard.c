#include <stdio.h>
#include <stdlib.h>

int len, drow, dcol;
int tileNum = 1;
int *board;

void black()
{
    printf("\033[1;30m");
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

void cyan()
{
    printf("\033[1;36m");
}

void white()
{
    printf("\033[1;37m");
}

void reset()
{
    printf("\033[0m");
}

void colour(int n)
{
    switch (n)
    {
    
    case 0:
        cyan();
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
        black();
        break;
    }
}

void printBoard()
{
    for(int i = 0 ; i < len ; i++)
    {
        for(int j = 0 ; j < len ; j++)
        {
            if(board[i*len + j] == 0)
                colour(-1);
            else
                colour(board[i*len + j]%6);
            printf("%d\t", board[i*len + j]);
        }
        printf("\n\n");
    }
}

void tileBoard(int topRow, int topCol , int defectRow ,int defectCol , int size)
{
    if (size == 1)
        return;
    
    int tileToUse=tileNum++;

    if (defectRow < topRow+size/2 && defectCol < topCol+size/2)
        tileBoard(topRow,topCol,defectRow,defectCol,size/2);
    else 
    {
        board[(topRow+size/2-1)*len + topCol+size/2-1]=tileToUse;
        tileBoard(topRow,topCol,topRow+size/2-1,topCol+size/2-1,size/2);
    }

    if (defectRow >= topRow+size/2 & defectCol < topCol+size/2)
        tileBoard(topRow+size/2,topCol,defectRow,defectCol,size/2);
    else 
    {
        board[(topRow+size/2)*len + topCol+size/2-1]=tileToUse;
        tileBoard(topRow+size/2,topCol,topRow+size/2,topCol+size/2-1,size/2);
    }

    if (defectRow < topRow+size/2 & defectCol >= topCol+size/2)
        tileBoard(topRow,topCol+size/2,defectRow,defectCol,size/2);
    else
    { 
        board[(topRow+size/2-1)*len + topCol+size/2]=tileToUse;
        tileBoard(topRow,topCol+size/2,topRow+size/2-1,topCol+size/2,size/2);
    }
    if (defectRow >= topRow+size/2 & defectCol >= topCol+size/2)
        tileBoard(topRow+size/2,topCol+size/2,defectRow,defectCol,size/2);
    else
    { 
        board[(topRow+size/2)*len + topCol+size/2]=tileToUse;
        tileBoard(topRow+size/2,topCol+size/2,topRow+size/2,topCol+size/2,size/2);
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
    tileBoard(0 , 0 , drow , dcol ,  len);
    printBoard();

    return 0;
}