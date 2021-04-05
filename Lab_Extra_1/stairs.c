#include <stdio.h>
#include <stdlib.h>

int stairs(int n)
{
    if(n <= 1)
        return n;
    return stairs(n-1) + stairs(n-2);
}
int main(int argc , char *argv[])
{
    if(argc != 2)
    {
        printf("invalid input");
        return 0;
    }

    int n = atoi(argv[1]);

    if(n < 0)
    {
        printf("invalid input");
        return 0;
    }

    printf("%d\n",stairs(n+1));
}