#include <stdio.h>
#include <stdlib.h>

int netsum = 18;

void initialize(int arr[] , int n)//initializer function for arrays
{
    for(int i = 0 ; i < n ; i++)
        arr[i] = 0;
}

void printSolution(int arr[], int x[] , int n)//prints solution vector in subset format
{
    printf("{");
    int c = 0;
    for(int i = 0 ; i < n ; i++)
        if(x[i+1])
        {
            if(c==0)
                printf("%d",arr[i]);
            else
                printf(",%d",arr[i]);
            c++;
        }
    printf("}\n");
}

void subsetSum(int arr[] , int x[] , int n, int i, int sum , int tempsum )//recursive function to form solution subset vectors
{
    if(x[i-1] && i != 1)//if previous x element is 1, add element to sum
        tempsum += arr[i-2];      
    if(tempsum == sum)//base case 1
    {
        printSolution(arr , x , n);
        return;
    }
    if(tempsum > sum)//base case 2
        return;
    if(i == n+1)//base case 3
        return;
    x[i] = 1;//left branch
    subsetSum(arr , x , n , i+1 , sum , tempsum);
    x[i] = 0;//right branch
    subsetSum(arr , x , n , i+1 , sum , tempsum);
    return;
}
int main(int argc, char *argv[])//driver function
{
    if(argc <= 3)
    {
        printf("invalid\n");
        return 0;
    }
    int n = atoi(argv[1]);
    if(argc != n + 3)
    {
        printf("invalid\n");
        return 0;
    }
    int arr[n];
    for(int i = 0 ; i < n ; i++)
        arr[i] = atoi(argv[i+2]);
    int sum = atoi(argv[argc - 1]);
    int x[7];
    initialize(x , 7);
    subsetSum(arr,x,n,1,sum,0);
}