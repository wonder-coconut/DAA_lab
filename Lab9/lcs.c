#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

int max(int a , int b)
{
    return a>b?a:b;
}

int min(int a, int b)
{
    return a>b?b:a;
}

void reverse(char * lcs, int len)
{
    char temp = 0;
    for(int i = 0 ; i < len/2 ; i++)
    {
        temp = lcs[i];
        lcs[i] = lcs[len - i - 1];
        lcs[len - i - 1] = temp;
    }
}

int lcsdriver(char *a , char *b , int la , int lb , char * lcs)
{
    int i,j;
    int table[la+1][lb+1];
    for(i = 0 ; i <= lb ; i++)
        table[0][i] = 0;
    for(i = 0 ; i <= la ; i++)
        table[i][0] = 0;
    
    for(i = 1 ; i <= la ; i++)
    {
        for(j = 1 ; j <= lb ; j++)
        {
            if(a[i-1] == b[j-1])
                table[i][j] = 1 + table[i-1][j-1];
            else
                table[i][j] = max(table[i-1][j] , table[i][j-1]);
        }
    }
    i = la;
    j = lb;
    int count = 0;

    while(i >= 0 && j >= 0 && table[i][j] != 0)
    {
        if(table[i-1][j] < table[i][j] && table[i][j-1] < table[i][j])
        {
            if(table[i][j] == 1 + table[i-1][j-1])
            {
                lcs[count] = lcs[count++];
                lcs[count-1] = a[i-1];
                i--;
                j--;
            }
        }
        else if(table[i-1][j] == table[i][j])
            i--;
        else if(table[i][j-1] == table[i][j])
            j--;
    }
    return count;
}
int main(int argc , char * argv[])
{
    if(argc != 5)
    {
        printf("invalid\n");
        return 0 ;
    }
    int la = atoi(argv[1]);
    int lb = atoi(argv[2]);
    char a[la];
    char b[lb];
    strcpy(a,argv[3]);
    strcpy(b,argv[4]);
    char * lcs;
    lcs = (char *)malloc(max(la,lb));
    int count = 0;
    count = lcsdriver(a,b,la,lb, lcs);
    reverse(lcs , count);
    printf("%s\n",lcs);
}