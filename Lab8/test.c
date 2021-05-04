#include <stdio.h>

int basen(int num , int base , char res[] , int i)//converts a decimal number to the specified base
{
    if(num == 0)
    {
        res[i++] = 0;
        return 0;
    }
    res[i++] = num%base; 
    basen(num/base , base , res , i);
}

int main()
{
    int n = 19;
    char arr[3];
    basen(n,3,arr,0);
    for(int i = 0 ; i < 3 ; i++)
        printf("%d ",arr[i]);
    printf("\n");
}