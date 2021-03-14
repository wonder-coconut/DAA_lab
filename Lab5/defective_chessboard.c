#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

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

double timeconvert(double sec , double msec)
{
    return sec + pow(10,-6)*msec;
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
    colour(-1);
}

void tileBoard(int row, int col , int defRow ,int defCol , int size)
{
    if (size == 1)
        return;
    
    int tile = tileNum++;

    if (defRow < row + size/2 && defCol < col + size/2)
        tileBoard(row,col,defRow,defCol,size/2);
    else 
    {
        board[(row + size/2-1)*len + col + size/2-1] = tile;
        tileBoard(row,col,row+size/2-1,col+size/2-1,size/2);
    }

    if (defRow >= row + size/2 && defCol < col + size/2)
        tileBoard(row+size/2,col,defRow,defCol,size/2);
    else 
    {
        board[(row + size/2)*len + col + size/2-1] = tile;
        tileBoard(row+size/2,col,row+size/2,col+size/2-1,size/2);
    }

    if (defRow < row + size/2 && defCol >= col + size/2)
        tileBoard(row,col+size/2,defRow,defCol,size/2);
    else
    { 
        board[(row + size/2-1)*len + col + size/2] = tile;
        tileBoard(row,col+size/2,row+size/2-1,col+size/2,size/2);
    }
    if (defRow >= row+size/2 && defCol >= col+size/2)
        tileBoard(row+size/2,col+size/2,defRow,defCol,size/2);
    else
    { 
        board[(row + size/2)*len + col + size/2] = tile;
        tileBoard(row+size/2,col+size/2,row+size/2,col+size/2,size/2);
    }
}

int main(int argc, char *argv[])
{
    struct timeval current_time;
    double baseTime, currentTime;
    int print;
    baseTime = currentTime = 0.0;

    len = atoi(argv[1]);
    drow = atoi(argv[2]);
    dcol = atoi(argv[3]);
    print = atoi(argv[4]);

    if(len == 0 || drow == 0 || dcol == 0 || drow > len || dcol > len)
    {
        printf("error");
        return 0;
    }

    gettimeofday(&current_time, NULL);
    baseTime = timeconvert(current_time.tv_sec , current_time.tv_usec);

    board = (int *)malloc(sizeof(int)*len*len);
    tileBoard(0 , 0 , drow , dcol ,  len);

    gettimeofday(&current_time, NULL);
    currentTime = timeconvert(current_time.tv_sec , current_time.tv_usec);
    printf("Runtime: %lf\n",currentTime - baseTime);

    FILE *fileOut;
    fileOut = fopen("TimeLog.txt","a");
    fprintf(fileOut,"%d\t%lf\n",len,(currentTime - baseTime));
    
    if (print == 1)
        printBoard();    

    return 0;
}