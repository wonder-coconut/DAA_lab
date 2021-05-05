#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void print2D(int arr[] , int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
            printf("%d\t",arr[i*n + j]);
        printf("\n");
    }
}

void print1D(int arr[] , int n)
{
    for(int i = 0 ; i < n ; i++)
        printf("%d ",arr[i]);
}

int efflength(int arr[] , int n)
{
    int count = 0;
    for(int i = 0 ; i < n ; i++)
        if(arr[i] != -1)
            count++;
    return count;
}

int g(int v , int sequence[] , int cost[] , int n_vertex)
{
    if(efflength(sequence , n_vertex) == 0)
        return cost[(v-1)*n_vertex + 0];
    int minimum,tempcost;
    minimum = INT_MAX;
    tempcost = 0;
    for(int k = 1 ; k <= n_vertex ; k++)
    {
        if(sequence[k-1] != -1)
        {
            tempcost = cost[(v-1)*n_vertex + k-1];
            sequence[k-1] = -1;
            tempcost += g(k , sequence , cost , n_vertex);
            sequence[k-1] = k;

            if(minimum > tempcost)
                minimum = tempcost;
        }
    }
    return minimum;
}

int tspdriver(int cost[] , int n_vertex)
{
    int sequence[n_vertex];
    for(int i = 0 ; i < n_vertex ; i++)
        sequence[i] = i + 1;
    sequence[0] = -1;
    return g(1 , sequence , cost , n_vertex);
}

int main()
{
    int n_vertex = 4;
    int cost[4*4] = {0,10,15,20,10,0,35,25,15,35,0,30,20,25,30,0};
    printf("%d\n",tspdriver(cost , n_vertex));
}