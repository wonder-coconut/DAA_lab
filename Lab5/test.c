#include <stdio.h>
#include <stdlib.h>

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
int main()
{
    for(int i = 1 ; i <= 20 ; i++)
    {
        colour(i%6);
        printf("UwU\n");
    }
    
    return 0;
}