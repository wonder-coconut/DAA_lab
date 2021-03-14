#include <stdio.h>
#include <stdlib.h>

int len;
void printArr(int arr[])
{
    for(int i = 0 ; i < len ; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int partition(int arr[] , int l , int r)
{
    int x = arr[r];
    int i = l - 1;
    int j;
    for(j = l ; j < r ; j++)
    {
        if(arr[j] <= x)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    ++i;
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    return i;
}

int quickSelect(int arr[] , int i, int l, int r)
{
    if (l == r)
        return arr[l];
    
    int pos = partition(arr, l, r);
    int count = pos - l + 1;
    if ( count == i )
        return arr[pos];
    else if ( count > i )      
        return quickSelect(arr, l, pos-1, i);
    else                 
        return quickSelect(arr, pos+1, r, i - count);   
}

int main(int argc , char *argv[])
{
    len = argc - 2;
    int i = atoi(argv[1])-1;
    int arr[len];

    for(int j = 0 ; j < len ; j++)
        arr[j] = atoi(argv[j+2]);

    printf("result : %d\n", quickSelect(arr, i , 0 , len - 1));
    printArr(arr);
    return 0;
}