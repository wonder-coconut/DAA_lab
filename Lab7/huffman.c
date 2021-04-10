#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct huffman_node
{
    int pos;
    char symbol;
    int freq;
    struct huffman_node * left , * right;
};

struct list
{
    struct huffman_node * data;
    struct list *next;
};

void initializeInt(int arr[] , int n)
{
    for(int i = 0 ; i < n ; i++)
        arr[i] = 0;
}

void initializeChar(char arr[] , int n)
{
    for(int i = 0 ; i < n ; i++)
        arr[i] = '\0';
}

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

int getFrequencyTable(char sym[] , int freq[])
{
    FILE* inputtext;
    inputtext = fopen("test.txt","r");

    char ch = ' ';
    int i,end;
    i = 0;
    end = -1;

    while((ch = fgetc(inputtext)) != EOF)
    {
        i = search(ch , sym , end);
        if(i == -1)
        {
            end = end + 1;
            sym[end] = ch;
            freq[end] = freq[end] + 1;
        }
        else
        {
            freq[i] = freq[i] + 1;
        }
    }
    fclose(inputtext);

    return end;
}

struct huffman_node * createnode(char symbol , int freq , int pos)
{
    struct huffman_node * temp = (struct huffman_node *)malloc(sizeof(struct huffman_node));
    temp->pos = pos;
    temp->symbol = symbol;
    temp->freq = freq;
    temp->left = temp->right = NULL;

    return temp;
}

void insertEnd(struct huffman_node *data , struct list *root)
{
    struct list *temp;
    temp = root;
    while(temp->next != NULL)
        temp = temp->next;
    
    
    temp->next = (struct list *)malloc(sizeof(struct list));
    temp->next->data = data;
    temp->next->next = NULL;
    
}

struct list * insertOrder(struct huffman_node *data , struct list *root)
{
    struct list *temp , *temp2;
    temp = root;

    if(temp->data->freq > data->freq)
    {
        temp = (struct list *)malloc(sizeof(struct list));
        temp->data = data;
        temp->next = root;
        root = temp;

        return root; 
    }

    while(temp->next != NULL)
    {
        if(data->freq < temp->next->data->freq)
            break;
        temp = temp->next;
    }

    temp2 = (struct list *)malloc(sizeof(struct list));
    temp2->data = data;
    temp2->next = temp->next;
    temp->next = temp2;

    return root;
}

struct list * deleteStart(struct list * root)
{
    return root->next;
}

void inorder(struct huffman_node * root)
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("|[%d] %c %d|",root->pos , root->symbol , root->freq);
        inorder(root->right);
    }
}

void preorder(struct huffman_node * root)
{
    if(root != NULL)
    {
        printf("|[%d] %c %d|",root->pos , root->symbol , root->freq);
        preorder(root->left);
        preorder(root->right);
    }
}

void printlist(struct list *root , int ch)
{
    struct list * temp;
    temp = root;

    while(temp != NULL)
    {
        if(ch == 0)
            inorder(temp->data);
        else if(ch == 1)
            preorder(temp->data);
        temp = temp->next;
        printf("\n");
    }
}

void printArray(int arr[] , int len)
{
    for(int i = 0 ; i < len ; i++)
        printf("%d ",arr[i]);
    
}

void printCharArray(char arr[] , int len)
{
    for(int i = 0 ; i < len ; i++)
        printf("%c ",arr[i]);
    
}

void printFrequencyTable(char sym[] , int freq[] , int n)
{
    for(int i = 0 ; i < n ; i++)
        printf("'%c':\t%d\n",sym[i] , freq[i]);
}

int listsize(struct list *root)
{
    int count = 0;
    struct list *temp;
    temp = root;

    while(temp != NULL)
    {
        temp = temp->next;
        count++;
    }

    return count;
}

struct list * huffmanTree(struct list *root)
{
    struct huffman_node * temp;
    temp = NULL;
    int f1,f2;
    f1 = f2 = 0;

    while(listsize(root) != 1)
    {
        f1 = root->data->freq;
        f2 = root->next->data->freq;
        temp = (struct huffman_node *)malloc(sizeof(struct huffman_node));

        temp->freq = f1+f2;
        temp->symbol = '\0';
        temp->pos = -1;
        temp->left = root->data;
        temp->right = root->next->data;

        root = insertOrder(temp , root);
        root = deleteStart(root);
        root = deleteStart(root);
        
    }

    return root;
}

void huffmancode(struct huffman_node * root , struct huffman_node * temp, int bin[], int binary)
{
    if(temp->left == NULL)
    {
        bin[temp->pos] = binary;
    }
    else
    {
        huffmancode(root , temp->left , bin , binary*2 + 0);
        huffmancode(root , temp->right, bin, binary*2 + 1);
    }
}

void printbinfile(char sym[] , int code[] , int len)
{
    FILE * binptr, *txtptr;
    txtptr = fopen("test.txt","r");
    binptr = fopen("test.bin","wb");

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
            ch = ch << bufflen;
            ch = ch | code[index];
            count += bufflen;
        }
        else
        {
            buffcode = code[index];
            templen = bufflen;

            for(i = 0 ; i < bufflen ; i++)
            {
                if(count == 8)
                {
                    fwrite(&ch , sizeof(ch) , 1 , binptr);
                    ch = 0;
                    count = 0;
                }
                ch = ch << 1;
                ch = ch | (buffcode/(int)(pow(2,templen-1)));
                count += 1;
                buffcode = buffcode % (int)(pow(2,templen-1));
                templen--;
            }
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

int main()
{
    char sym[255];
    int freq[255];

    initializeInt(freq , 255);
    initializeChar(sym , 255);

    int end = 0;
    end = getFrequencyTable(sym, freq);
    printFrequencyTable(sym , freq , end + 1);

    int code[end + 1];
    for(int i = 0 ; i <= end ; i++)
        code[i] = 0;

    struct list *root = (struct list *)malloc(sizeof(struct list));
    root->data = createnode(sym[0] , freq[0] , 0);
    root->next = NULL;

    int i = 1;
    for( ; i <= end ; i++)
        insertEnd( createnode(sym[i] , freq[i] , i) , root);
    
    root = huffmanTree(root);

    huffmancode(root->data , root->data , code , 0);

    printf("~~~~~~~~~~~~~~~~~~~~~~~\n");

    printlist(root , 0);

    printf("~~~~~~~~~~~~~~~~~~~~~~~\n");
    
    printCharArray(sym , end + 1);
    printf("\n");
    printArray(code , end + 1);

    printbinfile(sym , code , end + 1);

    return 0;
}