#include <stdio.h>
#include <stdlib.h>

int password(int n , int sum)//returns the password for the constraints
{
    if(sum == 0)//base constraints, zero sum
    {
        if(n == 1)//single digit zero sum
            return 0;
        else
            return -1;
    }
    else if(sum > 9*n)//max sum of n digits would be 9*n as each digit can have max value of 9
        return -1;
    
    int res = 0;

    for(int i = 0 ; i < n ; i++)//traversal from most to least significant digit
    {
        if(sum >= 9)//greedy method, highest digits will take most significant spots
        {
            res = res*10 + 9;
            sum = sum - 9;
        }
        else if(sum > 0 && sum < 9)
        {
            res = res*10 + sum;
            sum = 0;
        }
        else
            res = res*10 + 0;
    }

    return res;
}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("invalid input\n");
        return 0;
    }

    int n,s;
    n = atoi(argv[1]);
    s = atoi(argv[2]);

    printf("%d\n",password(n,s));
}