#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct team //structure to implement each element of the list
{
    int roll;
    char name[50];
    int team;
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

void merge(struct team *teamset , int l , int m , int r, int ch)
{

    int lenl = m - l + 1;
    int lenr = r - m;
    
    struct team L[lenl];
    struct team R[lenr];

    int i,j,k;
    i = j = k = 0;
    
    for(i = 0 ; i < lenl ; i++)
        equate(&L[i],&teamset[l+i]);

    for(i = 0 ; i < lenr ; i++)
        equate(&R[i],&teamset[m+i+1]);

    i = j = 0;
    k = l;


    while( i < lenl && j < lenr)
    {
        if(ch == 1)
        {
            if(L[i].roll < R[j].roll)
            {
                equate(&teamset[k],&L[i]);
                i++;
            }
            else
            {
                equate(&teamset[k],&R[j]);
                j++;
            }
        }
        else if(ch == 2)
        {
            if(L[i].team < R[j].team)
            {
                equate(&teamset[k],&L[i]);
                i++;
            }
            else
            {
                equate(&teamset[k],&R[j]);
                j++;
            }
        }
        else if(ch == 3)
        {
            if(strcmp(L[i].name,R[j].name) < 0)
            {
                equate(&teamset[k],&L[i]);
                i++;
            }
            else
            {
                equate(&teamset[k],&R[j]);
                j++;
            }
        }
        k++;
    }

    while(i < lenl)
    {
        equate(&teamset[k],&L[i]);
        k++;
        i++;
    }
    
    while(j < lenr)
    {
        equate(&teamset[k],&R[j]);
        k++;
        j++;
    }

}

void mergeSort(struct team *teamset , int l , int r, int ch)
{
    if(l < r)
    {
        int m = (l + r)/2;

        mergeSort(teamset , l , m, ch);
        mergeSort(teamset , m + 1 , r, ch);

        merge(teamset , l , m , r, ch);
    }
}




void printList(struct team *teamset, int len) //printing all elements, for convenience
{
    int i=0;
    while(i<len)
    {
        printf("%d %s %d\n",teamset[i].roll,teamset[i].name,teamset[i].team);
        i++;
    }
}

void printListFile(struct team * teamset, int len)//writing the list to the file
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

int main(int argc , char *argv[])//mainfunction
{
    int ch1 = 0;
    int ch2 = 0;
    //sanity checks for user input:
    if(argc !=3)//number of inputs
    {
        printf("insufficient input(s)");
        return 0;
    }

    ch1 = atoi(argv[1]);
    ch2 = atoi(argv[2]);

    if(!((ch1 == -1 || ch1 == 1 || ch1 == 2 || ch1 == 3) && (ch2 == 1 || ch2 == 2)) || (ch1 == 0 || ch2 == 0))
    {//checking whether inputs are integers and within the valid range
        printf("invalid choice:\t%d %d",ch1,ch2);
        return 0;
    }

    struct team teamset[86];
    int len = sizeof(teamset)/sizeof(teamset[0]);

    input(teamset, len);

    /*if(ch2 == 1)
        insertionSort(teamset,ch1);
    else if(ch2 == 2)
        selectionSort(teamset,ch1);*/
    int l, r;
    l = 0;
    r = len - 1;

    //printf("%d\n",len2);
    mergeSort(teamset, l, r, ch1);
    //printList(teamset,len);
    printListFile(teamset,len);
    return 0;
}