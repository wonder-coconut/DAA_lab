#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct team //structure to implement each element of the list
{
    int roll;
    char name[50];
    int team;
};

struct node
{
    struct team data;
    struct node* left;
    struct node* right;
};

int rollConvert(char roll[50]) //function to convert a string roll number to a usable integer, for sorting
{
    char res[2];
    for(int i = 0; i < 2 ; i++)
    {
        res[i] = roll[i+8];//slicing the last two digits from the roll number
    }
    int result = atoi(res);//conversion from string to integer
    return result;
}

void input(struct team *teamset, int len)//function to input data into struct array from file, for convenience
{
    FILE *fileInput;
    fileInput = fopen("DAALab_Input1.txt","r");

    char temp[50];
    int ch = 2;
    int i = 0;

    
    while(i<len)
    {
        fscanf(fileInput,"%s",temp);
        teamset[i].roll = rollConvert(temp);
        fscanf(fileInput,"%s",teamset[i].name);
        fscanf(fileInput,"%s",temp);
        teamset[i].team = atoi(temp);
        i++;
    }
    fclose(fileInput);
}

void equate(struct team *a,struct team *b)//equates two team structs
{
    a->roll = b->roll;
    strcpy(a->name,b->name);
    a->team = b->team;
}

void appendElementFile(struct team teamset)//function to append the element to a file
{
    FILE *fileOutput;
    fileOutput = fopen("DAALab_Output1.txt","a");
    char format[10];
    int i = 0;
    if(teamset.roll<10)
        strcpy(format,"19XJ1A050");//reformatting the roll number, as only the last two digits are sliced into the struct variable
    else
        strcpy(format,"19XJ1A05");
    
    fprintf(fileOutput,"%s%d %s %d\n",format,teamset.roll,teamset.name,teamset.team);
    fclose(fileOutput);
}

struct node* newNode(struct team teamset)
{
    struct node *temp;
    temp = (struct node*)malloc(sizeof(struct node));
    equate(&(temp->data),&teamset);
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void insert(struct node **root, struct team teamset)
{
    if(*root == NULL)
    {
        *root = newNode(teamset);
    }
    else
    {
        if(teamset.roll >= (*root)->data.roll)
        {
            insert(&((*root)->right),teamset);
        }
        else if(teamset.roll < (*root)->data.roll)
        {
            insert(&((*root)->left),teamset);
        }
    }
}

void inorder(struct node* root)
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("%d %s %d\n",root->data.roll,root->data.name,root->data.team);
        inorder(root->right);
    }
}

void inorderWrite(struct node* root)
{
    if(root != NULL)
    {
        inorderWrite(root->left);

        appendElementFile(root->data);

        inorderWrite(root->right);
    }
}

int main()//mainfunction
{
    struct team teamset[86];
    int len = sizeof(teamset)/sizeof(teamset[0]);

    input(teamset, len);
    
    struct node* root;
    root = NULL;

    for(int i = 0 ; i < len ; i++)
        insert(&root,teamset[i]);

    inorderWrite(root);

    return 0;
}