#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

int len = 1024;//dimension of matrix
int bl = 0;//dimension of block (will be set in main method)

int initialize(int *arr, int l , int u)//function to initialize the matrix with ranged pseudo-random numbers
{
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len; j++)
        {
            arr[i*len + j] = rand()%(u - l + 1) + l;
        }
    }
}

void blockMultiplier(int *A, int *B, int *C)//block matrix multiplier function
{
    for(int ii = 0 ; ii < len ; ii = ii + bl)//outer three loops iterate through each block, incremented by block length
    {                                        //for each iteration
        for(int jj = 0 ; jj < len ; jj = jj + bl)
        {
            for(int kk = 0 ; kk < len ; kk = kk + bl)
            {
                for(int i = ii ; i < ii + bl ; i++)//inner three loops iterate within the block limits
                {
                    for(int j = jj ; j < jj + bl ; j++)
                    {
                        for(int k = kk ; k < kk + bl ; k++)
                        {
                            C[i*len + j] += A[i*len + k] * B[k*len + j];//multiplication
                        }
                    }
                } 
            }
        }
    }

}

void printArray(int *arr)//function to print each element of the array
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



int main(int argc, char *argv[])//driver
{
    struct timeval current_time;//time function to calculate the runtim
    bl = atoi(argv[1]);//block length input

    if(bl!= 2 && bl!= 4 && bl!= 8 && bl!= 16)//sanity check
    {
        printf("invalid choice of block length\n");
        return 0;
    }

    gettimeofday(&current_time, NULL);
    double baseTime = current_time.tv_sec + pow(10,-6)*current_time.tv_usec;//base case time, for reference
    double currentTime = 0;

    int *A = (int *)malloc(sizeof(int)*len*len);//matrix declaration
    int *B = (int *)malloc(sizeof(int)*len*len);
    int *C = (int *)malloc(sizeof(int)*len*len);

    initialize(A,0,21);//matrix initialization
    initialize(B,0,21);
    initialize(C,0,0);

    gettimeofday(&current_time, NULL);
    currentTime = current_time.tv_sec + pow(10,-6)*current_time.tv_usec; // initialization time
    printf("Time for initialization : %lf\n",(currentTime - baseTime));

    blockMultiplier(A,B,C);
    
    gettimeofday(&current_time, NULL);
    currentTime = current_time.tv_sec + pow(10,-6)*current_time.tv_usec;
    printf("Time for block multiplication for size %d : %lf\n",4,(currentTime - baseTime));//multiplication runtime

    free(A);
    free(B);
    
    return 0;
}