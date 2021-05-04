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

int checkSort(struct team* teamset, int len, int ch)//checking whether the array is sorted
{
    int res = 1;
    for(int i = 0 ; i < len-1 ; i++)
    {
        if(ch == 1)
        {
            if(teamset[i].roll > teamset[i+1].roll)
            {
                res = 0;
                printf("%d\t%d\n",teamset[i].roll,teamset[i+1].roll);
            }
        }
        else if(ch == 2)
        {
            if(teamset[i].team > teamset[i+1].team)
            {
                res = 0;
                printf("%d\t%d\n",teamset[i].team,teamset[i+1].team);
            }
        }
        else if(ch == 3)
        {
            if(strcmp(teamset[i].name, teamset[i+1].name) > 0)
            {
                res = 0;
                printf("%s\t%s\n",teamset[i].name,teamset[i+1].name);
            }
        }
    }
    return res;
} 

void merge(struct team *teamset , int l , int m , int r, int ch)//merge two arrays in an ascending order
{

    int lenl = m - l + 1;
    int lenr = r - m;//length of the two arrays to be merged
    
    struct team L[lenl];
    struct team R[lenr];

    int i,j,k;//indices for left array, right array, and main array respectively
    i = j = k = 0;
    
    for(i = 0 ; i < lenl ; i++)//dividing array into two subarrays
        equate(&L[i],&teamset[l+i]);

    for(i = 0 ; i < lenr ; i++)
        equate(&R[i],&teamset[m+i+1]);

    i = j = 0;
    k = l;


    while( i < lenl && j < lenr)
    {
        if(ch == 1)//rollnumber
        {
            if(L[i].roll < R[j].roll)//adding the smallest of the two array elements continuously
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
        else if(ch == 2)//team number
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
        else if(ch == 3)//name sort
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
        else if(ch == -1)//priority sort, engages next priority field when encountering a case of equality
        {
            if(L[i].team < R[j].team)
            {
                equate(&teamset[k],&L[i]);
                i++;
            }
            else if(L[i].team == R[j].team)
            {
                if(L[i].roll < R[j].roll)
                {
                    equate(&teamset[k],&L[i]);
                    i++;
                }
                else if(L[i].team == R[j].team)
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
                else
                {
                    equate(&teamset[k],&R[j]);
                    j++;
                }          
            }
            else
            {
                equate(&teamset[k],&R[j]);
                j++;
            }
        }
        k++;
    }

    while(i < lenl)//adding remaining elements, if any (this occurs because lenl might not be equal to lenr)
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

void mergeSort(struct team *teamset , int l , int r, int ch)//sorting two arrays using recursive algorithms
{
    if(l < r)
    {
        int m = (l + r)/2;//midpoint for division of subarrays

        mergeSort(teamset , l , m, ch);//sorting left subarray
        mergeSort(teamset , m + 1 , r, ch);//sorting right subarray

        merge(teamset , l , m , r, ch);//merging the two subarrays
    }
}

int partition(struct team *teamset , int l , int r, int ch)//pivotless partition algorithm, where the pivot is found at the end of the partition
{
    int flag = 1;//variable to  act as a switch between incrementing l and decrementing r, shown better further in code
    int part = 0;//partition index

    while(l < r)
    {
        if(ch == 1)//roll
        {
            if(teamset[l].roll > teamset[r].roll)
            {
                swap(&teamset[l],&teamset[r]);//every time a swap occurs, the code switches from incrementing l to decrementing r, and vice versa
                flag++;//switching
            }
        }
        else if (ch == 2)//team
        {
            if(teamset[l].team > teamset[r].team)
            {
                swap(&teamset[l],&teamset[r]);
                flag++;
            }
        }
        else if (ch == 3)//name
        {
            if(strcmp(teamset[l].name, teamset[r].name) > 0)
            {
                swap(&teamset[l],&teamset[r]);
                flag++;
            }
        }
        else if (ch == -1)//priority field sort
        {
            if(teamset[l].team > teamset[r].team)
            {
                swap(&teamset[l],&teamset[r]);
                flag++;
            }
            else if(teamset[l].team == teamset[r].team)
            {
                if(teamset[l].roll > teamset[r].roll)
                {
                    swap(&teamset[l],&teamset[r]);
                    flag++;
                }
                else if(teamset[l].roll == teamset[r].roll)
                {
                    if(strcmp(teamset[l].name,teamset[r].name) > 0)
                    {
                        swap(&teamset[l],&teamset[r]);
                        flag++;
                    }
                }
            }
        }

        if(flag % 2 == 1)//every increment in flag will act as a switch
            l++;
        else
            r--;

        if(l == r)
            part = l;
    }

    //bringing the pivot element to the correct sorted position
    return part;//partition index
}

void quickSort(struct team *teamset, int l , int r, int ch)//recursive algorithm to sort an array with a pivot element
{
    if(l >= r)
        return;
    else
    {
        int part = partition(teamset, l , r, ch);//partition index

        quickSort(teamset, l, part - 1, ch);//sorting the left subarray
        quickSort(teamset, part + 1, r, ch);//sorting the right subarray
    }
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
    
    int l, r;
    l = 0;
    r = len - 1;

    if(ch2 == 1)
        mergeSort(teamset, l, r, ch1);

    else if(ch2 == 2)
        quickSort(teamset, l, r, ch1);

    //int res = checkSort(teamset, len, ch1);

    //printf("sort success: %d\n",res);
    printListFile(teamset,len);
    return 0;
}