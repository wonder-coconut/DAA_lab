#include <stdio.h>
#include <stdlib.h>


int findways(int m , int n , int x)
{
    int sum[n + 1][x + 1];
    for(int i = 0 ; i <= n ; i++)
        for(int j = 0 ; j <= x ; j++)
            sum[i][j] = 0;

    for (int j = 1; j <= m && j <= x; j++)
        sum[1][j] = 1;
  
    for (int i = 2; i <= n; i++)
        for (int j = 1; j <= x; j++)
            for (int k = 1; k <= m && k < j; k++)
                sum[i][j] += sum[i-1][j-k];
  
    return sum[n][x];
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