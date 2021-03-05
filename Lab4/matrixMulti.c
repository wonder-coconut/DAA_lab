#include <stdio.h>

void printArray(int crr[4][4], int len)
{
    for(int i = 0 ; i < len ; i++)
    {
        for(int j = 0 ; j < len ; j++)
        {
            printf("%d\t",crr[i][j]);
        }
        printf("\n");
    }
}

int multiply(int arr[4][4], int brr[4][4], int crr[4][4], int len)
{
    for(int i = 0 ; i < len ; i++)
    {
        for (int j = 0; j < len; j++)
        {
            for (int k = 0; k < len; k++)
            {
                crr[i][j] += (arr[i][k])*(brr[k][j]);
            }            
        }        
    }

    printArray(crr,4);
}

int main()
{
    int arr[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    int brr[4][4] = {{1,0,1,0},{0,1,0,1},{1,1,0,0},{1,0,0,1}};
    int crr[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

    multiply(arr,brr,crr,4);

    
}