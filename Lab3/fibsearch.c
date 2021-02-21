#include <stdio.h>
#include <math.h>

int arr[] = {1,2,3,4,5,6,7,8,9,10,11};
int len = 11;

int isPerfectSquare(int n)
{
    int root = sqrt(n);
    return (root*root == n);
}
int isFibonacci(int n)
{
    return (isPerfectSquare(5*n*n + 4) || isPerfectSquare(5*n*n - 4));
}
int fibIndex(int n)
{
    while(1)
    {
        if(isFibonacci(n))
            break;
        n++;
    }

    double invgoldenratio = 1/(0.5 * (1 + sqrt(5)));
    double res = invgoldenratio * invgoldenratio * n;
    int result = (int)round(res);
    return result;
}
int fibSearch(int l , int r, int search)
{
    if(l > r)
        return 0;
    else
    {
        int m = fibIndex(r - l + 1) + l;
        if(arr[m] == search)
            return 1;
        else
        {
            if(search < arr[m])
                fibSearch(l , m-1 , search);
            else
                fibSearch(m + 1, r , search);
        }
    }
}

int main()
{
    int res = fibSearch(0 , len - 1, 1);
    printf("%d\n",res);
}

