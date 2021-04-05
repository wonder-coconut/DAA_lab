#include <stdio.h>
#include <stdlib.h>

struct job
{
    int start;
    int finish;
};

void equate(struct job *a,struct job *b)//equates two job structs
{
    a->start = b->start;
    a->finish = b->finish;
}

void initialize(struct job *jobs , int S[] , int F[] , int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        jobs[i].start = S[i];
        jobs[i].finish = F[i];
    }
}

void printList(struct job *jobs, int l , int r) //printing all elements, for convenience
{
    int i=l;
    while(i<=r)
    {
        printf("%d %d\n",jobs[i].start,jobs[i].finish);
        i++;
    }
}

void printNode(struct job *a)
{
    printf("%d %d",a->start , a->finish);
}

void printArray(int arr[] , int n)
{
    for(int i = 0 ; i < n ; i++)
        printf("%d ",arr[i]);
    printf("\n");
}

void merge(struct job *jobs , int l , int m ,int r)
{
    int lenl = m - l + 1;
    int lenr = r - m;

    struct job left[lenl];
    struct job right[lenr];

    int i,j,k;
    i = j = k = 0;

    for(; i < lenl ; i++)
        equate(&left[i] , &jobs[l+i]);
    
    for(; j < lenr ; j++)
        equate(&right[j] , &jobs[m+j+1]);

    i = j = 0;
    k = l;

    while(i < lenl && j < lenr)
    {
        if(left[i].finish < right[j].finish)
        {
            equate(&jobs[k] , &left[i]);
            i++;
        }
        else
        {
            equate(&jobs[k] , &right[j]);
            j++; 
        }
        k++;
    }

    while(i < lenl)
    {
        equate(&jobs[k] , &left[i]);
        k++; i++;
    }
    while(j < lenr)
    {
        equate(&jobs[k] , &right[j]);
        k++; j++;
    }
}

void mergeSort(struct job *jobs , int l , int r )
{
    if(l < r)
    {
        int m = (r+l)/2;

        mergeSort(jobs , l , m);
        mergeSort(jobs, m+1 , r);

        merge(jobs , l , m , r);
    }
}

int meeting(struct job *jobs , int n)
{
    struct job *jobInitial;
    int count,i;
    jobInitial = &jobs[0];
    count = 1;
    i = 1;

    while(i < n)
    {
        if(jobs[i].start > jobInitial->finish)
        {
            count++;
            jobInitial = &jobs[i];
        }
        i++;
    }
    return count;
}

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);

    if(argc - 1 != 2*n + 1)
    {
        printf("invalid input\n");
        return 0;
    }

    int S[n];
    int F[n];

    for(int i = 0 ; i < n ; i++)
    {
        S[i] = atoi(argv[i+2]);
        F[i] = atoi(argv[i+n+2]);
        if(S[i] >= F[i] || S[i] < 0 || F[i] < 0)
        {
            printf("invalid input");
            return 0;
        }
    }

    struct job jobs[n];

    initialize(jobs , S , F , n);  

    mergeSort(jobs , 0 , n - 1);

    printf("%d\n",meeting(jobs , n));

    return 0;
}