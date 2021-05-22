#include <stdio.h>
#include <stdlib.h>

void printMatrix(int arr[] , int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
            printf("%d ",arr[i*n + j]);
        printf("\n");
    }
}

int isSafe(int arr[] , int i , int j , int n)
{
    int ii , jj;
    for(ii = 0 ; ii < n ; ii++)
    {
        for(jj = 0 ; jj < n ; jj++)
        {
            
            if(arr[ii*n + jj] == 1)
            {
                if(ii == i)
                    return 0;
                else if(jj == j)
                    return 0;
                else if(ii - jj == i - j)
                    return 0;
                else if(ii + jj == i + j)
                    return 0;
            }
        }
    }
    return 1;
}

int nqsolver(int arr[] , int n , int column)
{
    if(column == n)
        return 1;
    
    for(int i = 0 ; i < n ; i++)
    {
        if(isSafe(arr , i , column , n))
        {
            arr[i*n + column] = 1;
            if(nqsolver(arr , n , column + 1))
                return 1;
            arr[i*n + column] = 0;
        }
    }
    return 0;
}

void nqueens(int n)
{
    int arr[n*n];
    int i,j;
    i = j = 0;
    for(i = 0 ; i < n ; i++)
        for(j = 0 ; j < n ; j++)
            arr[i*n + j] = 0;
    
    int res = nqsolver(arr , n , 0);
    if(res)
        printMatrix(arr,n);
}

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        printf("invalid\n");
        return 0;
    }
    int n = atoi(argv[1]);
    
    nqueens(n);
}