#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int n_vertex;

int remlength(char arr[n_vertex])
{
    int count = 0;
    for(int i = 0 ; i < n_vertex ; i++)
        if(arr[i] != -1)
            count++;
    return count;
}
int tsp(int v , int *cost, char temp[])
{
    if(remlength(temp) == 0)
    {
        printf("cost at v,1:%d\n",cost[(v-1)*n_vertex + 0]);
        return cost[(v-1)*n_vertex + 0];
    }
    int minimum = INT_MAX;
    int t1,t2;
    t1 = t2 = 0;
    temp[v-1] = -1;
    for(int k = v + 1 ; k <= n_vertex ; k++)
    {
        if(temp[k-1] != -1)
        {
            t1 = cost[(v-1)*n_vertex + k - 1];
            t1 += tsp(k , cost , temp);

            if(minimum > t1)
                minimum = t1;
        }
    }
    return minimum;
}
void tspdriver(int *cost)
{
    char temp[n_vertex];
    for(int i = 0; i < n_vertex ; i++)
        temp[i] = i+1;
    printf("\ncost :\t%d\n",tsp(1 , cost  , temp));
    return;
}
int main(int argc , char *argv[])
{
    if(argc < 3)
    {
        printf("invalid\n");
        return 0;
    }
    n_vertex = atoi(argv[1]);
    if(argc != 2 + n_vertex * n_vertex) // total number of arguments
    {
        printf("invalid\n");
        return 0;
    }
    
    int cost[n_vertex][n_vertex];
    for(int i = 0 ; i < n_vertex ; i++)
        for(int j = 0 ; j < n_vertex ; j++)
            cost[i][j] = atoi(argv[i*n_vertex + j]);       
    
    tspdriver(&cost[0][0]);
    return 0;
}