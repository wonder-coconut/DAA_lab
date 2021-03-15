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

void merge(int ar1[] , int ar2[] , int n)
{
    int i,j,gap;
    i = j = gap = 0;

    for(gap = nextGap(2*n); gap > 0 ; gap = nextGap(gap))
    {
        for(i = 0; i + gap < n ; i++)
            if(ar1[i] > ar1[i+gap])
                swap(&ar1[i] , &ar1[i+gap]);

        if(gap > n)
            j = gap - n;
        else
            j = 0;

        while(i < n && j < n)
        {
            if(ar1[i] > ar2[j])
                swap(&ar1[i],&ar2[j]);
            
            i++;
            j++;
        }

        for(j = 0 ; j + gap < n ; j++)
        {
            if(ar2[j] > ar2[j+gap])
                swap(&ar2[j], &ar2[j+gap]);
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

    merge(ar1,ar2,len);

    double res = median(ar1,ar2);

    printf("%lf\n",res);

    return 0;
}