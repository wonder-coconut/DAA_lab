#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

int initialize(int *arr, int l , int u, int len)
{
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len; j++)
        {
            arr[i*len + j] = rand()%(u - l + 1) + l;
        }
    }
}

void printArray(int *arr, int len)
{
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len; j++)
        {
            printf("%d\t",arr[i*len + j]);
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

    int len = 5; 
    int *A = (int *)malloc(sizeof(int)*len*len);
    int *B = (int *)malloc(sizeof(int)*len*len);
    int *C = (int *)malloc(sizeof(int)*len*len);

    initialize(A,0,21,len);
    initialize(B,0,21,len);
    initialize(C,0,0,len);
    
    

    gettimeofday(&current_time, NULL);
    currentTime = current_time.tv_sec + pow(10,-6)*current_time.tv_usec;
    printf("Time for initialization : %lf\n",(currentTime - baseTime));


    free(A);
    free(B);
    return 0;
}