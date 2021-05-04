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

void printArrayFloat(float arr[] , int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}

int maximum(float pw[] , int n)//returns the index of the max element, and deleting the max element
{
    int i = 0;
    int max_index = 0;
    float max = pw[0];
    
    for( ; i < n ; i++)
    {
        if(pw[i] >= 0 && max < pw[i])
        {
            max = pw[i];
            max_index = i;
        }
    }

    pw[max_index] = -1;
    return max_index;
}

int min(int a , int b)
{
    return (a<b)?a:b;
}

void knapsack(int p[] , int w[] , float pw[] , float x[] , int n , int cap)//function to implement the greedy method of the knapsack problem
{
    int sack_weight = 0;
    int total_weight = 0;
    int max_index = 0;

    for(int i = 0 ; i < n ; i++)
    {
        total_weight += w[i];
    }

    while (sack_weight < min(cap , total_weight))
    {
        max_index = maximum( pw , n);        
        if(w[max_index] <= cap - sack_weight)//the whole object can be fit into the knapsack
        {
            x[max_index] = 1;
            sack_weight = sack_weight + w[max_index];
        }
        else if(cap > sack_weight)//a fraction of the object has to be fit into the knapsack
        {
            x[max_index] = (cap - sack_weight * 1.0) / w[max_index];
            sack_weight = cap;//this case will only occur with the last element, thus sack weight will become maximum weight
        }
    }  
}

int main(int argc , char *argv[])//driver
{
    int n = atoi(argv[1]);
    int cap = atoi(argv[argc - 1]);

    if(n <= 0 || argc - 1 != n*2 + 2)//sanity check
    {
        printf("Invalid input\n");
        return 0;
    }

    int p[n];
    int w[n];
    float pw[n];
    float x[n];

    for(int i = 0 ; i < n ; i++)
    {
        p[i] = atoi(argv[i+2]);//profit array
        w[i] = atoi(argv[i+n+2]);//weight array
        pw[i] =  (1.0  * p[i]) / w[i] ;//profit by weight array
        x[i] = 0;//solution vector
    }

    knapsack(p , w , pw , x , n , cap);

    printArrayFloat(x , n);

    return 0;
}
