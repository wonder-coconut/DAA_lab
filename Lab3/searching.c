#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct team //structure to implement each element of the list
{
    int roll;
    char name[50];
    int team;
};

struct team teamset[86];

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

void input(int len)//function to input data into struct array from file, for convenience
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

void swap(struct team *a,struct team *b)//swaps two elements of teamset array 
{
    int temp; char temps[50];

    temp = a->roll;//roll number swap
    a->roll = b->roll;
    b->roll = temp;

    strcpy(temps,a->name);//name swap
    strcpy(a->name,b->name);
    strcpy(b->name,temps);

    temp = a->team;//team number swap
    a->team = b->team;
    b->team = temp;
}

void equate(struct team *a,struct team *b)//equates two team structs
{
    a->roll = b->roll;
    strcpy(a->name,b->name);
    a->team = b->team;
}

void printList(int len) //printing all elements, for convenience
{
    int i=0;
    while(i<len)
    {
        printf("%d %s %d\n",teamset[i].roll,teamset[i].name,teamset[i].team);
        i++;
    }
}

void printListFile(int len)//writing the list to the file
{
    FILE *fileOutput;
    fileOutput = fopen("DAALab_Output1.txt","w");
    char format[10];
    int i = 0;
    while(i<len)
    {
        if(teamset[i].roll<10)
            strcpy(format,"19XJ1A050");//reformatting the roll number, as only the last two digits are sliced into the struct variable
        else
            strcpy(format,"19XJ1A05");
        
        fprintf(fileOutput,"%s%d %s %d\n",format,teamset[i].roll,teamset[i].name,teamset[i].team);
        i++;
    }
    fclose(fileOutput);
    
}

void appendElementFile(struct team teamset)
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

int linearSearch(int ch, char search[20], int len)
{
    int numSearch = 0;
    int res = 0;

    if(ch == 1 || ch == 2)
    {
        numSearch = atoi(search);
        if(numSearch == 0 && search[0] != '0')
        {
            printf("invalid input\n");
            return 0;
        }
    }

    for(int i = 0; i<len ; i++)
    {
        if(ch == 1)
        {
            if(teamset[i].roll == numSearch)
            {
                appendElementFile(teamset[i]);
                res = 1;
            }
        }
        else if(ch == 2)
        {
            if(teamset[i].team == numSearch)
            {
                appendElementFile(teamset[i]);
                res = 1;
            }
        }
        else if(ch == 3)
        {
            if(strcmp(teamset[i].name,search) == 0)
            {
                appendElementFile(teamset[i]);
                res = 1;
            }
        }
    }
    return res;
}

int main(int argc , char *argv[])//mainfunction
{
    int ch1 = 0;
    int ch2 = 0;
    char search[20];

    //sanity checks for user input:
    if(argc !=4)//number of inputs
    {
        printf("insufficient input(s)");
        return 0;
    }

    ch1 = atoi(argv[1]);
    ch2 = atoi(argv[2]);
    strcpy(search,argv[3]);

    if(!((ch1 == 1 || ch1 == 2 || ch1 == 3) && (ch2 == 1 || ch2 == 2 || ch2 == 3)) || (ch1 == 0 || ch2 == 0))
    {//checking whether inputs are integers and within the valid range
        printf("invalid choice:\t%d %d",ch1,ch2);
        return 0;
    }

    int len = sizeof(teamset)/sizeof(teamset[0]);

    input(len);

    int res = linearSearch(ch1,search,len);
    printf("%d\n",res);
    return 0;
}