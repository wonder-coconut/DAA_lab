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

void input(struct team *teamset)//function to input data into struct array from file, for convenience
{
    FILE *fileInput;
    fileInput = fopen("DAALab_Input1.txt","r");

    char temp[50];
    int ch = 2;
    int i = 0;
    
    while(i<86)
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

void merge(struct team *teamset , int l , int m , int r)
{

    int lenl = m - l + 1;
    int lenr = r - m;
    
    //int L[lenl], R[lenr];
    struct team L[lenl];
    struct team R[lenr];

    int i,j,k;
    i = j = k = 0;
    
    for(i = 0 ; i < lenl ; i++)
        //L[i] = teamset[l+i].roll;
        equate(&L[i],&teamset[i]);

    for(i = 0 ; i < lenr ; i++)
        //R[i] = teamset[m+i+1].roll;
        equate(&R[i],&teamset[i]);

    i = j = 0;
    k = l;


    while( i < lenl && j < lenr)
    {
        if(L[i].roll <= R[j].roll)
        {
            //teamset[k].roll = L[i];
            equate(&teamset[k],&L[i]);
            i++;
        }
        else
        {
            //teamset[k].roll = R[j];
            equate(&teamset[k],&R[j]);
            j++;
        }
        k++;
    }

    while(i < lenl)
    {
        //teamset[k].roll = L[i];
        equate(&teamset[k],&L[i]);
        k++;
        i++;
    }
    
    while(j < lenr)
    {
        //teamset[k].roll = R[j];
        equate(&teamset[k],&R[j]);
        k++;
        j++;
    }

}

void mergeSort(struct team *teamset , int l , int r)
{
    if(l < r)
    {
        int m = (l + r)/2;

        mergeSort(teamset , l , m);
        mergeSort(teamset , m + 1 , r);

        merge(teamset , l , m , r);
    }
}




void printList(struct team *teamset) //printing all elements, for convenience
{
    int i=0;
    while(i<86)
    {
        printf("%d %s %d\n",teamset[i].roll,teamset[i].name,teamset[i].team);
        i++;
    }
}

void printListFile(struct team * teamset)//writing the list to the file
{
    FILE *fileOutput;
    fileOutput = fopen("DAALab_Output1.txt","w");
    char format[10];
    int i = 0;
    while(i<86)
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
    input(teamset);

    /*if(ch2 == 1)
        insertionSort(teamset,ch1);
    else if(ch2 == 2)
        selectionSort(teamset,ch1);*/
    int l, r, len;
    len = 86;
    l = 0;
    r = len - 1;

    mergeSort(teamset, l, r);
    printListFile(teamset);
    return 0;
}