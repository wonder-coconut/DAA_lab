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

int search(char ch , char arr[] , int end)//binary search
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

int getFrequencyTable(char sym[] , int freq[])//function to get the frequency table from file
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
        if(i == -1)//new character
        {
            end = end + 1;
            sym[end] = ch;
            freq[end] = freq[end] + 1;//frequency increment
        }
        else
        {
            freq[i] = freq[i] + 1;
        }
    }
    fclose(inputtext);

    return end;
}

void merge(char sym[] , int freq[] , int l , int m , int r)
{
    int lenl = m - l + 1;
    int lenr = r - m;

    int fl[lenl] , fr[lenr];
    char sl[lenl] , sr[lenr];

    int i,j,k;
    i = j = k = 0;

    for( ; i < lenl ; i++)
    {
        fl[i] = freq[l+i];
        sl[i] = sym[l+i];
    }

    for( i = 0 ; i < lenr ; i++)
    {
        fr[i] = freq[m+i+1];
        sr[i] = sym[m+i+1];
    }

    i = j = 0;
    k = l;

    while(i < lenl && j < lenr)
    {
        if(fl[i] < fr[j])
        {
            freq[k] = fl[i];
            sym[k] = sl[i];
            i++;
            k++;
        }
        else
        {
            freq[k] = fr[j];
            sym[k] = sr[j];
            j++;
            k++;
        }
    }

    while(i < lenl)
    {        
        freq[k] = fl[i];
        sym[k] = sl[i];
        i++;
        k++;
    }

    while (j < lenr)
    {
        freq[k] = fr[j];
        sym[k] = sr[j];
        j++;
        k++;
    }
}

void mergesort(char sym[] , int freq[] , int l , int r)
{
    if(l < r)
    {
        int m = (l + r)/2;

        mergesort(sym , freq , l , m);
        mergesort(sym , freq , m+1 , r);

        merge(sym , freq , l , m , r);
    }
}

struct huffman_node * createnode(char symbol , int freq , int pos)//function to create huffman tree node
{
    struct huffman_node * temp = (struct huffman_node *)malloc(sizeof(struct huffman_node));
    temp->pos = pos;
    temp->symbol = symbol;
    temp->freq = freq;
    temp->left = temp->right = NULL;

    return temp;
}

void insertEnd(struct huffman_node *data , struct list *root)//insert list node at end
{
    struct list *temp;
    temp = root;
    while(temp->next != NULL)
        temp = temp->next;
    
    
    temp->next = (struct list *)malloc(sizeof(struct list));
    temp->next->data = data;
    temp->next->next = NULL;
    
}

struct list * insertOrder(struct huffman_node *data , struct list *root)//insert list node in ascending order
{
    struct list *temp , *temp2;
    temp = root;

    if(temp->data->freq > data->freq)//first element insert
    {
        temp = (struct list *)malloc(sizeof(struct list));
        temp->data = data;
        temp->next = root;
        root = temp;

        return root; 
    }

    while(temp->next != NULL)
    {
        if(data->freq < temp->next->data->freq)//finding position to insert
            break;
        temp = temp->next;
    }

    temp2 = (struct list *)malloc(sizeof(struct list));
    temp2->data = data;
    temp2->next = temp->next;//insertion
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

void printlist(struct list *root , int ch)//print list contents
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

void printbinfile(char sym[] , int code[] , int len , unsigned char * finalbyte , int * finalcount)//write compressed binary file
{
    FILE * binptr, *txtptr;
    txtptr = fopen("test.txt","r");
    binptr = fopen("output.bin","wb");

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
        
        if(8 - count >= bufflen)//direct addition of character code
        {
            ch = ch << bufflen;
            ch = ch | code[index];
            count += bufflen;
        }
        else//bitwise addition of character code
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
                ch = ch | (buffcode/(int)(pow(2,templen-1)));//bit extraction
                count += 1;
                buffcode = buffcode % (int)(pow(2,templen-1));
                templen--;
            }
        }

        if(count == 8)//write buffer
        {
            fwrite(&ch , sizeof(ch) , 1 , binptr);
            ch = 0;
            count = 0;
        }
    }

    if(ch != 0)//final byte write
    {
        ch = ch << (8 - count);
        fwrite(&ch , sizeof(ch) , 1 , binptr);
    }
    fclose(binptr);
    fclose(txtptr);

    *finalbyte = ch;
    *finalcount = count;
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

struct list * huffmanTree(struct list *root)//function to generate huffman tree
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

void huffmancode(struct huffman_node * root , struct huffman_node * temp, int bin[], int binary)//huffman encoding
{
    if(temp->left == NULL)
    {
        bin[temp->pos] = binary;
    }
    else
    {
        huffmancode(root , temp->left , bin , binary*2 + 0);//left subtree
        huffmancode(root , temp->right, bin, binary*2 + 1);//right subtree
    }
}

void decoder(struct huffman_node *root , unsigned char * finalbyte , int  * finalcount)//binary file decoder
{
    struct huffman_node *temp;
    temp = root;
    unsigned char ch = 0;
    int bin , count , lim;
    bin = count = 0;
    lim = 8;

    FILE *binptr , *textptr;
    binptr = fopen("output.bin","rb");
    textptr = fopen("decompressed.txt","w");
    
    while(!feof(binptr))
    {
        ch = fgetc(binptr);

        if(ch == *finalbyte)
        {
            for(int i = 0 ; i < lim - 1 ; i++)//writes until number of specified bits, instead of full byte
            {
                if(temp->symbol != '\0')//until leaf node is encountered
                {
                    fprintf(textptr , "%c" , temp->symbol);
                    temp = root;
                }

                bin = ch/(int)pow(2,7);//most significant bit

                if(bin)
                    temp = temp->right;
                else
                    temp = temp->left;

                ch = ch << 1;//left shift
            }
            break;
        }

        while(count < 8)
        {

            if(temp->symbol != '\0')
            {
                printf("%c",temp->symbol);
                fprintf(textptr , "%c" , temp->symbol);
                temp = root;
            }

            count++;
            bin = ch/(int)pow(2,7);
            
            if(bin)
                temp = temp->right;
            else
                temp = temp->left;

            ch = ch << 1;
        }
        count = 0;
    }

    
}

int main(int argc , char * argv[])//driver
{
    if(argc == 1)
    {
        printf("invalid input \n");
        return 0;
    }

    int flag = atoi(argv[1]);

    char sym[255];
    int freq[255];

    initializeInt(freq , 255);
    initializeChar(sym , 255);

    int end = 0;
    end = getFrequencyTable(sym, freq);

    mergesort(sym , freq , 0 , end);

    printFrequencyTable(sym , freq, end + 1);

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

    printArray(code , end + 1);
    printf("\n");

    unsigned char finalbyte;
    int finalcount;
    finalbyte = finalcount = 0;
    printbinfile(sym , code , end + 1 , &finalbyte , &finalcount);

    printf("%x %d\n",finalbyte,finalcount);

    if(flag == 1)
        decoder(root->data , &finalbyte , &finalcount);

    return 0;
}