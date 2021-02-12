#include <stdio.h>

void printArr(int arr[] , int len)
{
    for(int i = 0 ; i < len ; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void swap(int * a , int * b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[] , int l , int r, int pivot)
{
    int left, right;

    left = l+1;
    right = r;

    while(left < right)
    {
        while(arr[left] < pivot)
            left++;

        while(arr[right] > pivot)
            right--;

        if(left >= right)
            break;
        else
            swap(&arr[left],&arr[right]);
    }
    
    swap(&arr[right],&arr[l]);
    return right;
}

void quickSort(int arr[], int l , int r)
{
    if(l >= r)
        return;
    else
    {
        int pivot = arr[l];
        int part = partition(arr, l , r, pivot);

        quickSort(arr, l, part - 1);
        quickSort(arr, part + 1, r);
    }
}

int main()
{
    int arr[] = { 9, 14, 6, 15, 8, 11, 20, 16, 7, 1};
    int len;
    len = sizeof(arr)/sizeof(arr[0]);
    int l,r;
    l = 0;
    r = len - 1;
    printf("Unsorted:\n");
    printArr(arr,len);

    quickSort(arr, l, r);

    printf("Sorted:\n");
    printArr(arr,len);
}