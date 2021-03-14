#include <stdio.h>

void recurse()
{
    printf("LOL!");
    recurse();
}

int main()
{
    recurse();
    return 0;
}