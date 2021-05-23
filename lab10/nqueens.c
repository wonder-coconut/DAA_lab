#include <stdio.h>
#include <stdlib.h>

void printFileMatrix(int arr[] , int n)//utility function
{
    FILE *foutput;
    foutput = fopen("nqueen.txt","a");
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
            if(arr[i*n + j] == 0)
                fprintf(foutput,"- ");
            else
                fprintf(foutput,"q ");
        fprintf(foutput,"\n");
    }
    fprintf(foutput,"----------------------------------------\n");
    fclose(foutput);
}

int isSafe(int arr[] , int i , int j , int n)//checks if the position is safe with current orientation of queens
{
    int ii , jj;
    for(ii = 0 ; ii < n ; ii++)
    {
        for(jj = 0 ; jj < n ; jj++)
        {
            
            if(arr[ii*n + jj] == 1)
            {
                if(ii == i)//row check
                    return 0;
                else if(jj == j)//column check
                    return 0;
                else if(ii - jj == i - j)//right diagonal check
                    return 0;
                else if(ii + jj == i + j)//left diagonal check
                    return 0;
            }
        }
    }
    return 1;
}

int nqsolver(int arr[] , int n , int column)//recursive function to fill the matrix
{
    if(column == n)//all queens are filled
        return 1;
    
    for(int i = 0 ; i < n ; i++)//row wise checking
    {
        if(isSafe(arr , i , column , n))//checking each element validity
        {
            arr[i*n + column] = 1;
            if(nqsolver(arr , n , column + 1))//recursively fill the other queens
                return 1;
            arr[i*n + column] = 0;//only executed if the previous condition is false, i.e. queen is in the wrong position
        }
    }
    return 0;//no solution
}

void nqueens(int n)//driver for nqsolver
{
    int arr[n*n];//chessboard
    int i,j;
    i = j = 0;
    for(i = 0 ; i < n ; i++)
        for(j = 0 ; j < n ; j++)
            arr[i*n + j] = 0;
    
    int res = nqsolver(arr , n , 0);
    if(res)//if a solution exists
        printFileMatrix(arr,n);
}

int main(int argc, char * argv[])//main driver
{
    if(argc != 2)
    {
        printf("invalid\n");
        return 0;
    }
    int n = atoi(argv[1]);
    
    nqueens(n);
}