#include <stdio.h>
#include <stdlib.h>


int findways(int m , int n , int x)
{
    int sum = 0;
    if(n == 1)
        return 1;
    for(int i = 1 ; i <= m && x - i > 0; i++)
        sum += findways(m , n - 1, x - i);
    return sum;
}
int main(int argc, char *argv[])
{
    int m,n,x;
    m = n = x = 0;

    if(argc != 4)
    {
        printf("Invalid input\n");
        return 0;
    }
    m = atoi(argv[1]);    
    n = atoi(argv[2]);
    x = atoi(argv[3]);
    if(m < 1 || n < 1 || x < 1)
    {
        printf("Invalid input\n");
        return 0;
    }

    printf("%d\n",findways(m,n,x));
    return 0;
}