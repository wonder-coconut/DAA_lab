#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

int initialize(int *arr, int l , int u)
{
    for(int i = 0; i < 1024; i++)
    {
        for(int j = 0; j < 1024; j++)
        {
            arr[i*1024 + j] = rand()%(u - l + 1) + l;
        }
    }
}

void printArray(int *arr)
{
    for(int i = 0; i < 1024; i++)
    {
        for(int j = 0; j < 1024; j++)
        {
            printf("%d\t",arr[i*1024 + j]);
        }
        printf("\n");
    }
}

int main()
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    double baseTime = current_time.tv_sec + pow(10,-6)*current_time.tv_usec;
    double currentTime = 0;
    
    int *arr = (int *)malloc(sizeof(int)*1024*1024);
    initialize(arr,0,21);
    //printArray(arr);

    gettimeofday(&current_time, NULL);
    currentTime = current_time.tv_sec + pow(10,-6)*current_time.tv_usec;
    printf("Time for initialization : %lf\n",(currentTime - baseTime));

    

    free(arr);
    return 0;
}