#include <stdio.h>


void printArr(int arr[] , int len)
{
    for(int i = 0 ; i < len ; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void swap(int arr[] , int l , int r)
{
    int temp = arr[l];
    arr[l] = arr[r];
    arr[r] = temp;
}

int main()
{
    int arr[] = {1,4,2,3,5,6};
    int len = 6;
    swap(arr,1,4);
    printArr(arr,len);
    return 0;
}