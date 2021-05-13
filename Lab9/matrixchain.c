#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct sym
{
    struct sym * prev;
    char ch;
    struct sym * next;
};

int min (int a , int b)
{
    return (a>b ? b : a);
}
int chaincalc(int* table , int*sequence , int* p, int i, int j , int n)
{
	if (i == j)
		return 0;
	if (table[i*n + j] != -1)
        return table[i*n + j];

	table[i*n + j] = INT_MAX;
    int temp = 0;
	for (int k = i; k < j; k++)
	{
        temp = chaincalc(table ,sequence ,p, i, k , n) + chaincalc(table , sequence, p, k + 1, j, n) + p[i - 1] * p[k] * p[j];
        if(min(temp,table[i*n + j]) == temp)
        {
            sequence[i*n + j] = k;
            table[i*n + j] = temp;
        }
    }
	return table[i*n + j];
}

void printsequence(int i , int j , int n , char *sym, int *sequence)
{
    if(i == j)
    {
        printf("%c",*sym);
        *sym = *sym + 1;
        return;
    }
    
    printf("(");
    printsequence(i , sequence[i*n + j] , n , sym , sequence);
    printsequence(sequence[i*n + j] + 1 , j , n , sym , sequence);
    printf(")");
}

void printOptimal(int *sequence , int n)
{
    char sym = 'A';
    
    printsequence(1 , n-1 , n , &sym ,sequence);
}
int MatrixChainOrder(int* p, int n)
{
	int i = 1, j = n - 1;

    int table[n*n];
    int sequence[n*n];
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < n ; j++)
        {
            sequence[i*n + j] = -1;
            table[i*n + j] = -1;
        }
	int res = chaincalc(table ,sequence , p, i, j , n);
    /*for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
            printf("%d|%d\t",table[i*n + j],sequence[i*n + j]);
        printf("\n");
    }*/
    printOptimal(sequence , n);
    return res;
}

int main()
{
	int arr[] = { 40,20,30,10,30 };
	int n = 5;

	printf("\n%d\n",MatrixChainOrder(arr, n));
}

