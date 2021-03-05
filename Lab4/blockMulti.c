#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

int len = 1024;
int bl = 16;

int initialize(int *arr, int l , int u)
{
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len; j++)
        {
            arr[i*len + j] = rand()%(u - l + 1) + l;
        }
    }
}

void blockMultiplier(int *A, int *B, int *C)
{
    for(int ii = 0 ; ii < len ; ii = ii + bl)
    {
        for(int jj = 0 ; jj < len ; jj = jj + bl)
        {
            for(int kk = 0 ; kk < len ; kk = kk + bl)
            {
                for(int i = ii ; i < ii + bl ; i++)
                {
                    for(int j = jj ; j < jj + bl ; j++)
                    {
                        for(int k = kk ; k < kk + bl ; k++)
                        {
                            C[i*len + j] += A[i*len + k] * B[k*len + j];
                        }
                    }
                } 
            }
        }
    }

}

void printArray(int *arr)
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

    int *A = (int *)malloc(sizeof(int)*len*len);
    int *B = (int *)malloc(sizeof(int)*len*len);
    int *C = (int *)malloc(sizeof(int)*len*len);

    initialize(A,0,21);
    initialize(B,0,21);
    initialize(C,0,0);
    
    /*printArray(A);
    printf("\n");
    printArray(B);
    printf("\n");
    printArray(C);
    printf("\n");*/

    gettimeofday(&current_time, NULL);
    currentTime = current_time.tv_sec + pow(10,-6)*current_time.tv_usec;
    printf("Time for initialization : %lf\n",(currentTime - baseTime));

    blockMultiplier(A,B,C);
    
    /*printArray(C);
    printf("\n");*/

    gettimeofday(&current_time, NULL);
    currentTime = current_time.tv_sec + pow(10,-6)*current_time.tv_usec;
    printf("Time for block multiplication for size %d : %lf\n",4,(currentTime - baseTime));

    free(A);
    free(B);
    return 0;
}