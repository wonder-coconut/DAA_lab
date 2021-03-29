#include <stdio.h>
#include <stdlib.h>

void printArrayInt(int arr[] , int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int maximum(int arr[] , int n , int f)//returns the index of the max element, and choice for deleting the max element
{
    int i = 0;
    int max_index = 0;
    int max = arr[0];
    
    for( ; i < n ; i++)
    {
        if(arr[i] >= 0 && max < arr[i])
        {
            max = arr[i];
            max_index = i;
        }
    }

    if(f)
        arr[max_index] = -1;
    return max_index;
}

int min(int a , int b)
{
    return (a<b)?a:b;
}

void sequencer(int p[] , int d[] , int n)//function to sequence jobs using greedy algorithm
{
    int cap = d[maximum(d , n , 0)];//max deadline
    int x[cap];//array to store the timeline/solution vector
    int i = 0;
    for( ; i < cap ; i++)
        x[i] = 0;
    i = 0;

    int count = 0;
    while(count < min(cap,n))
    {
        printf("%d\t",count);
        printArrayInt(x , cap);
        int job = maximum(p , n , 1);//most profitable job
        
        for(i = d[job] - 1 ; i >= 0 ; i--)//using latest possible deadline for each job
        {
            if(x[i] == 0)
            {
                x[i] = job + 1;
                count++;
                break;
            }
        }
    }

    printArrayInt(x , cap);
}

int main(int argc , char *argv[])//driver
{
    int n = atoi(argv[1]);

    if(n <= 0 || argc - 1 != n*2 + 1)//sanity check
    {
        printf("Invalid input\n");
        return 0;
    }

    int p[n];//profit array
    int d[n];//deadline array

    for(int i = 0 ; i < n ; i++)
    {
        p[i] = atoi(argv[i+2]);//profit array
        d[i] = atoi(argv[i+n+2]);//deadline array
    }

    sequencer(p , d , n);

    return 0;
}