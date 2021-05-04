#include <stdio.h>
#include <stdlib.h>

int count( int S[], int m, int n )
{
    int i,j,x,y;
    int table[n+1][m];
    
    for (i=0; i<m; i++)
        table[0][i] = 1;
    for (i = 1; i < n+1; i++)
        for (j = 0; j < m; j++)
        {
            if(i-S[j] >= 0)
                x = table[i - S[j]][j];
            else
                x = 0;

            if(j >= 1) 
                y = table[i][j-1];
            else
                y = 0;
            table[i][j] = x + y;
        }

    return table[n][m-1];
}
int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        printf("Invalid input\n");
        return 0;
    }
    int m = atoi(argv[1]);
    if(argc != m + 3)
    {
        printf("Invalid input\n");
        return 0;
    }
    int arr[m];
    int n = atoi(argv[argc-1]);
    for(int i = 0 ; i < m ; i++)
        arr[i] = atoi(argv[i+2]);
    
    printf("%d\n", count(arr, m, n));
    return 0;
}