#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int search(char ch , char arr[] , int end)
{
    for(int i = 0 ; i <= end ; i++)
    {
        if(arr[i] == ch)
            return i;
    }
    return -1;
}

int ispoweroftwo(int n)
{
    return floor(log2(n)) == ceil(log2(n));
}

int main()
{
    FILE * binptr, *txtptr;
    txtptr = fopen("test.txt","r");
    binptr = fopen("test.bin","wb");
    char sym[] = {'a','b','c','d','e','f'};
    int code[] = {12,13,4,5,7,0}; //1100 1101 100 101 111 0
    int len = 6;

    int codeLen[6];
    int i = 0;
    for( ; i < len ; i++)
    {
        if(code[i])
            codeLen[i] = (int)(ceil(log2(code[i])))  + ispoweroftwo(code[i])*1;
        else
            codeLen[i] = 1;
    }

    unsigned char ch = 0;
    char symbol = '\0';
    int j , index, count , bufflen , buffcode, templen;
    i = j = index = count = bufflen = buffcode = templen =  0;

    while((symbol = fgetc(txtptr)) != EOF)
    {
        index = search(symbol , sym , len);
        bufflen = codeLen[index];
        
        if(8 - count >= bufflen)
        {
            printf("%x (%d) becomes",ch,count);
            ch = ch << bufflen;
            ch = ch | code[index];
            count += bufflen;
            printf(" %x (%d) when count > buffer\n",ch , count);
        }
        else
        {
            printf("for count < buffer (symbol : %c || code : %d):\n%x (%d)\n ",symbol ,code[index],ch , count);
            buffcode = code[index];
            templen = bufflen;

            for(i = 0 ; i < bufflen ; i++)
            {
                if(count == 8)
                {
                    printf("writing %x to bin\n",ch);
                    fwrite(&ch , sizeof(ch) , 1 , binptr);
                    ch = 0;
                    count = 0;
                }
                printf("append: %d (%d) to %x, resulting in ",buffcode/(int)(pow(2,templen-1))  , count, ch);
                ch = ch << 1;
                ch = ch | (buffcode/(int)(pow(2,templen-1)));
                count += 1;
                buffcode = buffcode % (int)(pow(2,templen-1));
                templen--;
                printf("%x (%d)\n",ch , count);
            }
            printf("final:%x (%d)\n",ch,count);
        }

        if(count == 8)
        {
            fwrite(&ch , sizeof(ch) , 1 , binptr);
            ch = 0;
            count = 0;
        }
    }

    if(ch != 0)
    {
        ch = ch << (8 - count);
        fwrite(&ch , sizeof(ch) , 1 , binptr);
    }
    fclose(binptr);
    fclose(txtptr);
}