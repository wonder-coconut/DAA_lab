#include <stdio.h>
#include <stdlib.h>


int main()
{

    FILE *fptr;
    fptr = fopen("testbin.bin","wb");

    unsigned char ch=0;
    char bin[] = "100101101010010110110100101";
    int len = 27;
    int i=0;

    while(i < len)
    {
        ch = ch | (bin[i] - '0');

        if((i+1) % 8 == 0)
        {
            fwrite(&ch , sizeof(ch) , 1 , fptr);
            ch = 0;
        }
        if(i != len - 1)
            ch = ch << 1;
        i++;
    }
    
    
    if(ch != 0)
        fwrite(&ch , sizeof(ch) , 1, fptr);

    fclose(fptr);

}