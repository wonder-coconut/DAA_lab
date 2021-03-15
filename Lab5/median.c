#include <stdio.h>
#include <stdlib.h>

int len;

void printArray(int arr[] , int size)
{
    for(int i = 0 ; i < size ; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n\n");
}
int sort(int arr[])
{
    for(int i = 1 ; i < len ; i++)
    {
        if(arr[i] < arr[i-1])
            return 0;
    }
    return 1;
}

int nextGap(int gap)
{
    if (gap <= 1)
        return 0;
    return (gap / 2) + (gap % 2);
}
void swap(int *n1, int *n2)
{
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

void merge(int* arr1, int* arr2, int n, int m)
{
    int i, j, gap = n + m;
    for (gap = nextGap(gap);gap > 0; gap = nextGap(gap)) 
    {
        // comparing elements in the first array.
        for (i = 0; i + gap < n; i++)
            if (arr1[i] > arr1[i + gap])
                swap(&arr1[i], &arr1[i + gap]);
 
        // comparing elements in both arrays.
        for (j = gap > n ? gap - n : 0;i < n && j < m;i++, j++)
            if (arr1[i] > arr2[j])
                swap(&arr1[i], &arr2[j]);
 
        if (j < m) {
            // comparing elements in the second array.
            for (j = 0; j + gap < m; j++)
                if (arr2[j] > arr2[j + gap])
                    swap(&arr2[j], &arr2[j + gap]);
        }
    }
}

double median(int ar1[],int ar2[])
{
    return (ar1[len-1] + ar2[0] + 0.0)/2;
}

int main(int argc , char *argv[])
{
    if((argc-1)%2 == 1)
    {
        printf("Invalid Input\n");
        return 0;
    }

    len = (argc-1)/2;
    int ar1[len],ar2[len];

    for(int i = 0 ; i < len ; i++)
    {
        ar1[i] = atoi(argv[i+1]);
        ar2[i] = atoi(argv[i+len+1]);
    }

    if(!sort(ar1) || !sort(ar2))
    {
        printf("Invalid input\n");
        return 0;
    }

    int arr[2*len];

    printArray(ar1,len);
    printArray(ar2,len);

    merge(ar1,ar2,len,len);

    printArray(ar1,len);
    printArray(ar2,len);

    double res = median(ar1,ar2);

    printf("%lf\n",res);

    return 0;
}