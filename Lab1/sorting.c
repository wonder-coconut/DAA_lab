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

void selectionSort(struct team *teamset,int ch) //implementing selection sort, with a choice for field of sorting
{
    int temp = 0;
    int minIndex = 0;//to store the minimum value element, as per selection sort algorithm
    for(int i = 0 ; i < 85 ; i++)
    {
        for(int j = i ; j < 86 ; j++)//loop starting from the unsorted array, to get the minimum unsorted element
        {
            if(ch == 1)//roll number sort
            {
                if (teamset[j].roll < teamset[minIndex].roll)
                {
                    minIndex = j;
                }
            }
            else if(ch == 2)//team sort
            {
                if (teamset[j].team < teamset[minIndex].team)
                {
                    
                    minIndex = j;
                }                
            }
            else if(ch == 3)//name sort
            {
                if(strcmp(teamset[j].name,teamset[minIndex].name) < 0)
                {
                    minIndex = j;
                }
                //printf("compare: %d %d\t",minIndex,strcmp(teamset[j].name,teamset[minIndex].name));
            }
            else if(ch == -1)//field priority sort
            {
                if (teamset[j].team < teamset[minIndex].team)//top priority to team
                {
                    minIndex = j;
                }
                else if(teamset[j].team == teamset[minIndex].team)//team stalemate
                {
                    if (teamset[j].roll < teamset[minIndex].roll)//second priority to roll
                    {
                        minIndex = j;
                    }
                    else if(teamset[j].roll == teamset[minIndex].roll)//roll number stalemate
                    {
                        if(strcmp(teamset[j].name,teamset[minIndex].name) < 0)//third priority to name
                        {
                            minIndex = j;
                        } 
                    }
                }
            }    
        }
        if(minIndex != i && minIndex > i)//prevention of swapping with the same index element 
            swap(&teamset[minIndex],&teamset[i]);//swapping the minimum element with the current element, sorting
    }
}

void insertionSort(struct team *teamset,int ch)//implementing insertionSort, with choice for field
{
    int i,j;
    i = j = 0;

    struct team temp;//temporary variable
    temp.roll = 0;
    strcpy(temp.name,"");
    temp.team = 0;

    for(i = 1 ; i < 86 ; i++)//outer 'i' loop iterates the array, where 'i' points to the element to be inserted
    {
        equate(&temp,&teamset[i]);//creating a copy of the element at 'i', this will be the value which will be inserted at the end

        for(j = i-1 ; j >= 0 ; j--)//iterates from the element before 'i' , until an element smaller than 'i'th element is encountered
        {
            if(ch == 1)//roll
            {
                if(teamset[j].roll  <= temp.roll)
                    break;
            }
            else if(ch == 2)//team
            {
                if(teamset[j].team <= temp.team)
                    break;              
            }
            else if(ch == 3)//name
            {
                if(strcmp(teamset[j].name,temp.name) <= 0)
                    break;
            }
            else if(ch == -1)
            {
                if(teamset[j].team  < temp.team)
                    break;
                else if(teamset[j].team == temp.team)//team stalemate
                {
                    if(teamset[j].roll < temp.roll)
                        break;
                    else if(teamset[j].roll == temp.roll)//roll number stalemate
                    {
                        if(strcmp(teamset[j].name,temp.name) < 0)
                            break;
                    }
                }
            }
            equate(&teamset[j+1],&teamset[j]);//shifting all elements larger than 'i' to the right
        }
        equate(&teamset[j+1],&temp);//insertion of the 'i'th element
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

    if(ch2 == 1)
        insertionSort(teamset,ch1);
    else if(ch2 == 2)
        selectionSort(teamset,ch1);
    printListFile(teamset);
    return 0;
}