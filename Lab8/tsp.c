#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int search(int arr[] , int n , int term)//linear search
{
    for(int i = 0 ; i < n ; i++)
        if(arr[i] == term)
            return i;
    return -1;
}

void print1D(int arr[] , int n)//print 1D array
{
    for(int i = 0 ; i < n ; i++)
        printf("%d ",arr[i]);
}

int efflength(int arr[] , int n)//length of array without -1's
{
    int count = 0;
    for(int i = 0 ; i < n ; i++)
        if(arr[i] != -1)
            count++;
    return count;
}

int g(int v , int sequence[] , int cost[] , int n_vertex , int tour[] , int counter)//recursive function to find the minimum cost
{
    if(efflength(sequence , n_vertex) == 0)//base case
        return cost[(v-1)*n_vertex + 0];
    int minimum,tempcost;
    minimum = INT_MAX;
    tempcost = 0;
    for(int k = 1 ; k <= n_vertex ; k++)
    {
        if(sequence[k-1] != -1)
        {
            tempcost = cost[(v-1)*n_vertex + k-1];//cost of (v,k)
            sequence[k-1] = -1;
            tempcost += g(k , sequence , cost , n_vertex , tour , counter + 1);//recursive relation
            sequence[k-1] = k;//restoring sequence

            if(minimum > tempcost)
            {
                if(search(tour , n_vertex , k) == -1 && search(tour , n_vertex , v) != -1)//printing tour
                    tour[counter] = k;
                minimum = tempcost;
            }
        }
    }
    return minimum;
}

int tspdriver(int cost[] , int n_vertex)//driver for tsp
{
    int sequence[n_vertex];
    int tour[n_vertex];
    for(int i = 0 ; i < n_vertex ; i++)
    {
        tour[i] = 0;
        sequence[i] = i + 1;
    }
    sequence[0] = -1;
    tour[0] = 1;
    int res = g(1 , sequence , cost , n_vertex , tour , 1);
    print1D(tour , n_vertex);
    return res;
}

int main(int argc, char *argv[])//program driver
{
    int n_vertex;
    n_vertex = atoi(argv[1]);
    int cost[n_vertex * n_vertex];
    for(int i = 0 ; i < n_vertex*n_vertex ; i++)
        cost[i] = atoi(argv[i+2]);
    printf("\n%d\n",tspdriver(cost , n_vertex));
}