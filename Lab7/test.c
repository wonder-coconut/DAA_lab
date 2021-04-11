#include <stdio.h>

struct huffman_node
{
    int pos;
    char symbol;
    int freq;
    struct huffman_node * left , * right;
};

void decoder(struct huffman_node *root)
{
    struct huffman_node *temp;
    temp = root;
    unsigned char ch = 0;
    int bin , count;
    bin = count = 0;

    FILE *binptr , *textptr;
    binptr = fopen("output.bin","rb");
    textptr = fopen("decompressed.txt","w");
    
    while((ch = fgetc(binptr)) != EOF)
    {
        while(count <= 8)
        {
            count++;
            bin = ch%2;
            if(bin)
                temp = temp->right;
            else
                temp = temp->left;
            if(temp->symbol != '\0')
            {
                fprintf(textptr , "%c" , ch);
                temp = root;
            }
            ch = ch << 1;
        }
        count = 0;
    }
}