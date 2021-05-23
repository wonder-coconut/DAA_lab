#include <stdio.h>
#include <stdlib.h>

void red()
{printf("\033[1;31m");}
void green()
{printf("\033[1;32m");}
void yellow()
{printf("\033[1;33m");}
void blue()
{printf("\033[1;34m");}
void purple()
{printf("\033[1;35m");}
void cyan()
{printf("\033[1;36m");}
void white()
{printf("\033[1;37m");}
void reset()
{printf("\033[0m");}
void colourset(int n)//colour driver
{
    switch (n)
    {
        case 0:red();break;
        case 1:green();break;
        case 2:yellow();break;
        case 3:blue();break;
        case 4:purple();break;
        case 5:cyan();break;
        case 6:white();break;
        default:reset();break;
    }
}

void printColouredSolution(int colour[] , int n)//formatting colour vector in coloured solution output
{
    char ch = 'a';
    for(int i = 0 ; i < n ; i++)
    {
        colourset(colour[i]);
        printf("%c ",ch++);
    }
    printf("\n");
}

void printArray(int arr[] , int n)
{
    for(int i = 0 ; i < n ; i++)
        printf("%d ",arr[i]);
    printf("\n");
}

int cancolour(int cost[] , int colourset[] , int n , int vertex , int colour)//checks if vertex can be coloured with specific colour
{
    for(int j = 0 ; j < n ; j++)
    {
        if(cost[(vertex - 1)*n + j] == 1)//adjacent vertex check
            if(colourset[j] == colour)
                return 0;
    }
    return 1;
}

int graphcolour(int cost[] , int n , int colourset[] , int vertex , int maxcolour , int count)
{
    if(vertex > n)//base case
        if(count == n)//all colours filled
            return 1;
        else
            return 0;
    for(int colour = 0 ; colour < maxcolour ; colour++)//colours represented as integers
    {
        if(cancolour(cost , colourset, n , vertex , colour))
        {
            colourset[vertex-1] = colour;//set colour
            count++;
            if(graphcolour(cost , n , colourset , vertex + 1 , maxcolour , count))//backtracking
                return 1;
            colourset[vertex - 1] = -1;//if false, colour reset
            count--;
        }
    }
    return 0;//no colour configuration for given parameters
}
void graphcolourdriver(int cost[] , int n , int colourflag)
{
    int colourset[n];
    for(int i = 0 ; i < n ; i++)
        colourset[i] = -1;
    int m;
    int res = 0;
    for(m = 1 ; m <= n ; m++)//iterating max number of colours, from minimum to maximum
    {
        if(graphcolour(cost , n , colourset , 1 , m, 0))
            break;
    }
    printf("Chromatic number: %d\n",m);//minimum colours
    if(colourflag == 1)//coloured solution
        printColouredSolution(colourset , n);
    else
        printArray(colourset , n);
}
int main(int argc , char *argv[])//driver function
{
    if(argc <= 2)
    {
        printf("invalid\n");
        return 0;
    }
    int n = atoi(argv[1]);
    if(argc != n*n + 2)
    {
        printf("invalid\n");
        return 0;
    }
    int cost[n*n];
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
            cost[i*n + j] = atoi(argv[i*n + j +2]);
    }
    graphcolourdriver(cost , n , 1);   
}