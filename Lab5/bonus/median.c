#include <stdio.h>
#include <stdlib.h>

int len;

void printArray(int arr[] , int l, int r)//prints array
{
    for(int i = l ; i <= r ; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

int checkSort(int arr[])//checks whether the array is sorted ascending
{
    for(int i = 1 ; i < len ; i++)
    {
        if(arr[i] < arr[i-1])
            return 0;
    }
    return 1;
}

double median(int arr[], int l , int r)//returns median of a sorted array
{
    if((r - l + 1) % 2 == 1)//odd size
        return arr[(l+r)/2];
    else                    //even size
        return (arr[(l+r)/2] + arr[(l+r)/2 + 1])/2.0;
}

double medianDriver(int ar1[] ,int ar2[] , int l1 , int r1 , int l2 , int r2)//function to get median of two sorted arrays
{
    if(r1 == l1)//base case
        return (ar1[l1] + ar2[l2])/2.0;

    double m1 = median(ar1, l1 , r1);
    double m2 = median(ar2 , l2 , r2);
    
    if(m1 == m2)//two equal medians of two arrays would mean that's the median of the combined array
        return m1;
    else if(m2 > m1)//comparing the medians
    {   //right subarray for array 1, left subarray for array 2
        if((r1-l1+1)%2 == 0)
            return medianDriver(ar1, ar2 , (l1+r1)/2 + 1 , r1 , l2 , (l2+r2)/2);
        else
            return medianDriver(ar1, ar2, (l1+r1)/2 + 1, r1 , l2 , (l2+r2)/2 - 1);
    }
    else if(m1 > m2)
    {   //left subarray for array 1, right subarray for array 2
        if((r1-l1+1)%2 == 0)
            return medianDriver(ar1, ar2 , l1 , (l1+r1)/2 , (l2+r2)/2 + 1 , r2);
        else
            return medianDriver(ar1, ar2, l1, (l1+r1)/2 -1 , (l2+r2)/2 + 1 , r2);
    }
}

int main(int argc , char *argv[])//driver function
{
    if((argc-1)%2 == 1)//sanity check
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

    if(!checkSort(ar1) || !checkSort(ar2))//sanity check
    {
        printf("Invalid input\n");
        return 0;
    }

    double res = medianDriver(ar1,ar2,0,len - 1 , 0 , len -1);

    printf("%lf\n",res);

    return 0;
}