#include <stdio.h>

void printArr(int arr[] , int len)
{
    for(int i = 0 ; i < len ; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void merge(int arr[] , int l , int m , int r)
{

    int lenl = m - l + 1;
    int lenr = r - m;
    
    int L[lenl], R[lenr];

    int i,j,k;
    i = j = k = 0;
    
    for(i = 0 ; i < lenl ; i++)
        L[i] = arr[l+i];

    for(i = 0 ; i < lenr ; i++)
        R[i] = arr[m+i+1];

    i = j = 0;
    k = l;


    while( i < lenl && j < lenr)
    {
        if(L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < lenl)
    {
        arr[k] = L[i];
        k++;
        i++;
    }
    
    while(j < lenr)
    {
        arr[k] = R[j];
        k++;
        j++;
    }

}
void mergeSort(int arr[] , int l , int r)
{
    if(l < r)
    {
        int m = (l + r)/2;

        mergeSort(arr , l , m);
        mergeSort(arr , m + 1 , r);

        merge(arr , l , m , r);
    }
}

int main()
{
    int arr[] = {5,4,7,2,8,9,1,0,3,6,-5,-10};
    int l,r,len;
    len = 12;
    l = 0;
    r = len - 1;

    printArr(arr,len);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    mergeSort(arr,l,r);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printArr(arr,len);
    return 0;
}