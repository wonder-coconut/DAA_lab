#include <stdio.h>

int search(char ch , char arr[] , int end)
{
    int l,m,r;
    l = 0;
    r = end;
    while(l < r)
    {
        m = (l + r)/2;
        if(arr[m] == ch)
            return m;
        else
        {
            if(arr[m] < ch)
                l = m + 1;
            else
                r = m - 1;
        }
    }
    return -1;
}

int main()
{
    char arr[] = {'a','b','c','d','e'};
    int len = 5;

    printf("%c\n",arr[search('c',arr,len-1)]);

    return 0;
}