#include <stdio.h>
#include <stdlib.h>

int len;

void printArr(int arr[])//prints array
{
    for(int i = 0 ; i < len ; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void swap(int *a , int *b)//swaps two elements
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int arr[] , int l , int r)//returns a random partition for the array
{
    int i = l - 1;

    for(int j = l ; j < r ; j++)
    {
        if(arr[j] < arr[r])
        {
            i++;
            swap(&arr[i] , &arr[j]);
        }
    }

    i++;
    swap(&arr[i],&arr[r]);
    return i;
}

int quickSelect(int arr[] , int i, int l, int r)//finds the ith smallest number
{
    int pos = partition(arr,l,r);
    
    if( pos == i)
        return arr[i];
    else if(pos > i)
        return quickSelect(arr, i , l , pos - 1);
    else
        return quickSelect(arr, i , pos + 1, r);
}

int main(int argc , char *argv[])//driver
{
    len = argc - 2;
    int i = atoi(argv[1])-1;
    if(i <= 0 || i >= len)
    {
        printf("Invalid input");
        return 0;
    }
    int arr[len];

    for(int j = 0 ; j < len ; j++)
        arr[j] = atoi(argv[j+2]);

    printf("result : %d\n", quickSelect(arr, i , 0 , len - 1));
    printArr(arr);
    return 0;
}