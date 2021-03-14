#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

int len;

double timeconvert(double sec , double msec)
{
    return sec + pow(10,-6)*msec;
}

void initialize(int *temp, int l , int u, int size)//function to initialize the matrix with ranged pseudo-random numbers
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            temp[i*size + j] = rand()%(u - l + 1) + l;
        }
    }
}

void printArray(int *temp)//function to print each element of the tempay
{
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len; j++)
        {
            printf("%d\t",temp[i*len + j]);
        }
        printf("\n");
    }
    printf("\n");
}

int * add(int *M1, int *M2, int *temp, int size)
{
    for(int i = 0 ; i < size ; i++)
    {
        for(int j = 0; j < size ; j++)
        {
            temp[i*size + j] = M1[i*size + j] + M2[i*size + j];
        }
    }

    return temp;
}

int * subtract(int *M1, int *M2, int *temp, int size)
{
    for(int i = 0 ; i < size ; i++)
    {
        for(int j = 0; j < size ; j++)
        {
            temp[i*size + j] = M1[i*size + j] - M2[i*size + j];
        }
    }

    return temp;
}

void multiply(int *A , int *B ,int *C, int size)
{
    initialize(C,0,0,size);
    for(int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                C[i*size + j] += A[i*size + k] * B[k*size + j];
            }   
        }
    }
}

int * strassenMultiply(int *A , int *B , int *C,int size)
{
    if(size == 1)
    {
        C[0] = A[0] * B[0];
        return C; 
    }

    int n = size/2;

    int *temp1 = (int *)calloc(n*n, sizeof(int));
    int *temp2 = (int *)calloc(n*n, sizeof(int));

    int *A11 = (int *)calloc(n*n,sizeof(int));
    int *A12 = (int *)calloc(n*n,sizeof(int));
    int *A21 = (int *)calloc(n*n,sizeof(int));
    int *A22 = (int *)calloc(n*n,sizeof(int));
    
    int *B11 = (int *)calloc(n*n,sizeof(int));
    int *B12 = (int *)calloc(n*n,sizeof(int));
    int *B21 = (int *)calloc(n*n,sizeof(int));
    int *B22 = (int *)calloc(n*n,sizeof(int));

    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            A11[i*n + j] = A[i*size + j];
            A12[i*n + j] = A[i*size + j + n];        
            A21[i*n + j] = A[(i + n)*size + j];      
            A22[i*n + j] = A[(i + n)*size + j + n];  
            B11[i*n + j] = B[i*size + j];
            B12[i*n + j] = B[i*size + j + n];
            B21[i*n + j] = B[(i + n)*size + j];
            B22[i*n + j] = B[(i + n)*size + j + n];
        }
    }

    int *M1 = (int *)calloc(n*n,sizeof(int));
    strassenMultiply(add(A11,A22,temp1,n),add(B11,B22,temp2,n),M1,n);

    int *M2 = (int *)calloc(n*n,sizeof(int));
    strassenMultiply(add(A21,A22,temp1,n),B11,M2,n);

    int *M3 = (int *)calloc(n*n,sizeof(int));
    strassenMultiply(A11,subtract(B12,B22,temp1,n),M3,n);

    int *M4 = (int *)calloc(n*n,sizeof(int));
    strassenMultiply(A22,subtract(B21,B11,temp1,n),M4,n);

    int *M5 = (int *)calloc(n*n,sizeof(int));
    strassenMultiply(add(A11,A12,temp1,n),B22,M5,n);

    int *M6 = (int *)calloc(n*n,sizeof(int));
    strassenMultiply(subtract(A21,A11,temp1,n),add(B11,B12,temp2,n),M6,n);

    int *M7 = (int *)calloc(n*n,sizeof(int));
    strassenMultiply(subtract(A12,A22,temp1,n),add(B21,B22,temp2,n),M7,n);

    
    int *C11 = (int *)calloc(n*n,sizeof(int));
    int *C12 = (int *)calloc(n*n,sizeof(int));
    int *C21 = (int *)calloc(n*n,sizeof(int));
    int *C22 = (int *)calloc(n*n,sizeof(int));

    subtract(add(add(M1,M4,C11,n),M7,C11,n),M5,C11,n);
    add(M3,M5,C12,n);
    add(M2,M4,C21,n);
    subtract(add(add(M1,M3,C22,n),M6,C22,n),M2,C22,n);

    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            C[i*size + j] = C11[i*n + j];
            C[i*size + j + n] = C12[i*n + j];
            C[(i + n)*size + j] = C21[i*n + j];
            C[(i + n)*size + j + n] = C22[i*n + j];
        }
    }

    return C;
}

int main(int argc, char *argv[])
{
    struct timeval current_time;
    double baseTime, currentTime;
    int print;

    len = atoi(argv[1]);
    print = atoi(argv[2]);

    int *A = (int *)malloc(sizeof(int)*len*len);//matrix declaration
    int *B = (int *)malloc(sizeof(int)*len*len);
    int *C = (int *)calloc(len*len,sizeof(int));
    int *temp;

    initialize(A,0,9,len);//matrix initialization
    initialize(B,0,9,len); 

    gettimeofday(&current_time , NULL);
    baseTime = timeconvert(current_time.tv_sec , current_time.tv_usec);

    strassenMultiply(A,B,C,len);

    gettimeofday(&current_time , NULL);
    currentTime = timeconvert(current_time.tv_sec , current_time.tv_usec);

    FILE *fileOut;
    fileOut = fopen("TimeLogDC.txt","a");
    fprintf(fileOut,"%d\t\t%lf\n",len,(currentTime - baseTime));
    printf("Time for multiplication: %lf\n",currentTime-baseTime);

    if(print == 1)
    {
        printArray(A);
        printArray(B);
        printArray(C);
    }

    free(A);
    free(B);
    free(C);
    return 0;
}