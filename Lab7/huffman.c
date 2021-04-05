#include <stdio.h>


void initializeInt(int arr[] , int n)
{
    for(int i = 0 ; i < n ; i++)
        arr[i] = 0;
}

void initializeChar(char arr[] , int n)
{
    for(int i = 0 ; i < n ; i++)
        arr[i] = NULL;
}

void printArrayInt(int arr[] , int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void printArrayChar(char arr[] , int n)
{
    for (int i = 0; i < n || arr[i] != NULL; i++)
    {
        printf("%c ",arr[i]);
    }   
}

int main()
{
    FILE* file;
    file = fopen("test.txt","r");
    char symbols[255];
    int frequency[255];

    initializeInt(frequency , 255);
    initializeChar(symbols , 255);

    printArrayInt(frequency , 255);
    printArrayChar(symbols , 255);
    symbols[0] = 'a';
    symbols[1] = 'b';    
}