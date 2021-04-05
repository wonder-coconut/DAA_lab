#include <stdio.h>
#include <stdlib.h>

int paths(int n)
{
    int a,b,c;
    a = 0;
    b = 1;
    c = 1;

    for(int i = 0 ; i < n ; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }

    return c;
}
 
int main(int argc, char *argv[])
{
    if(argc < 1)
    {
        printf("invalid input\n");
        return 0;
    }

    int n = atoi(argv[1]);
    
    if(n < 0)
    {
        printf("invalid input\n");
        return 0;
    }

    printf("%d",paths(n));
}