#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void merge(int l , int m , int r, int ch)//merge two arrays in an ascending order
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

void mergeSort(int l , int r, int ch)//sorting two arrays using recursive algorithms
{
    if(l < r)
    {
        int m = (l + r)/2;//midpoint for division of subarrays

        mergeSort(l , m, ch);//sorting left subarray
        mergeSort(m + 1 , r, ch);//sorting right subarray

        merge(l , m , r, ch);//merging the two subarrays
    }
}

int linearSearch(int ch, char search[20], int len)//function to implement linear search
{
    int numSearch = 0;
    int res = 0;

    if(ch == 1 || ch == 2)//numeric inputs
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
        if(ch == 1)//roll
        {
            if(teamset[i].roll == numSearch)
            {
                appendElementFile(teamset[i]);
                res = 1;
            }
        }
        else if(ch == 2)//team
        {
            if(teamset[i].team == numSearch)
            {
                appendElementFile(teamset[i]);
                res = 1;
            }
        }
        else if(ch == 3)//name
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

void duplicateElement(int ch, int index, int numSearch, char search[20])//to print duplicate elements in binary and fibonacci search
{
    int i = index + 1;

    while(1)//right
    {
        if(ch == 1)
        {
            if(teamset[i].roll != numSearch)//base case (non duplicate elements)
                break;
            else
            {
                appendElementFile(teamset[i]);
                i++;
            }
        }        
        else if(ch == 2)
        {
            if(teamset[i].team != numSearch)
                break;
            else
            {
                appendElementFile(teamset[i]);
                i++;
            }
        }
        else if(ch == 3)
        {
            if(strcmp(teamset[i].name,search) != 0)
                break;
            else
            {
                appendElementFile(teamset[i]);
                i++;                
            }
        }
    }

    i = index - 1;

    while(1)//left
    {
        if(ch == 1)
        {
            if(teamset[i].roll != numSearch)
                break;
            else
            {
                appendElementFile(teamset[i]);
                i--;
            }
        }        
        else if(ch == 2)
        {
            if(teamset[i].team != numSearch)
            {
                break;
            }
            else
            {
                appendElementFile(teamset[i]);
                i--;
            }
        }
        else if(ch == 3)
        {
            if(strcmp(teamset[i].name,search) != 0)
                break;
            else
            {
                appendElementFile(teamset[i]);
                i--;                
            }
        }
    }
}

int binarySearch(int l , int r, int ch , char search[20] , int numSearch)//implementing binary search
{
    int m = l - (l-r)/2;//split array into halves
        
    if(l > r)//base case
    {
        return 0;
    }
    else
    {
        if(ch == 1)//roll
        {
            if(teamset[m].roll == numSearch)
            {
                appendElementFile(teamset[m]);
                duplicateElement(ch, m, numSearch,NULL);
                return 1;
            }
            else
            {
                if(numSearch > teamset[m].roll)//left right limit updation according to relative position of search element
                    l = m + 1;

                else
                    r = m - 1;
                
                binarySearch(l , r, ch ,NULL, numSearch);//recursive search
            }            
        }
        else if(ch == 2)//team
        {
            if(teamset[m].team == numSearch)
            {
                appendElementFile(teamset[m]);
                duplicateElement(ch, m, numSearch,NULL);
                return 1;
            }
            else
            {
                if(numSearch > teamset[m].team)
                    l = m + 1;

                else
                    r = m - 1;
                
                binarySearch(l , r, ch , NULL, numSearch);
            }    
        }
        else if(ch == 3)//name
        {
            if(strcmp(teamset[m].name,search) == 0)
            {
                appendElementFile(teamset[m]);
                duplicateElement(ch, m, 0, search);
                return 1;
            }
            else
            {
                if(strcmp(search, teamset[m].name) < 0)
                    r = m - 1;
                else
                    l = m + 1;
                binarySearch(l , r , ch , search, 0);
            }
        }
    }
}

int binaryDriver(int ch , char search[20] , int len)//driver function for binary search
{
    mergeSort(0, len - 1, ch);//sort

    int numSearch = 0;
    int res = 0;

    if(ch == 1 || ch == 2)//numeric input
    {
        numSearch = atoi(search);
        if(numSearch == 0 && search[0] != '0')
        {
            printf("invalid input\n");
            return 0;
        }
    }
    res = binarySearch(0, len - 1 , ch , search, numSearch);
    return res;
}

int isPerfectSquare(int n)//checking for perfect square
{
    int root = sqrt(n);
    return (root*root == n);
}

int isFibonacci(int n)//checking for fibonacci number
{
    return (isPerfectSquare(5*n*n + 4) || isPerfectSquare(5*n*n - 4));
}

int fibIndex(int n)//returns the index for division of array
{
    while(1)
    {
        if(isFibonacci(n))//smallest fibonacci number larger than length n
            break;
        n++;
    }

    double invgoldenratio = 1/(0.5 * (1 + sqrt(5)));//golden ratio value
    double res = invgoldenratio * invgoldenratio * n;//approximate value of fibonacci number two positions behind n
    int result = (int)round(res);//rounded to nearest integer for exact value
    return result;
}

int fibSearch(int l , int r, int ch, char search[20] , int numSearch)//implementation of fibonacci search
{
    if(l > r)//base case
        return 0;
    else
    {
        int m = fibIndex(r - l + 1) + l;//second largest fibonacci number smaller than length

        if(ch == 1)//roll
        {
            if(teamset[m].roll == numSearch)
            {
                appendElementFile(teamset[m]);
                duplicateElement(ch, m, numSearch, NULL);
                return 1;
            }
            else
            {
                if(numSearch < teamset[m].roll)
                    r = m - 1;//left right limit updation according to relative position of search element
                else
                    l = m + 1;
                fibSearch(l , r, ch , NULL, numSearch);//recursive search
            }
        }
        else if(ch == 2)//team
        {
            if(teamset[m].team == numSearch)
            {
                appendElementFile(teamset[m]);
                duplicateElement(ch, m, numSearch, NULL);
                return 1;
            }
            else
            {
                if(numSearch < teamset[m].team)
                    r = m - 1;
                else
                    l = m + 1;
                fibSearch(l , r, ch , NULL, numSearch);
            }
        }
        else if(ch == 3)//name
        {
            if(strcmp(teamset[m].name,search) == 0)
            {
                appendElementFile(teamset[m]);
                duplicateElement(ch, m, 0, search);
                return 1;
            }
            else
            {
                if(strcmp(search, teamset[m].name) < 0)
                    r = m - 1;
                else
                    l = m + 1;
                fibSearch(l , r , ch , search, 0);
            }
        }
    }
}

int fibonacciDriver(int ch , char search[20], int len)//driver function for fibonacci search
{
    mergeSort(0, len - 1, ch);//sort

    int numSearch = 0;
    int res = 0;

    if(ch == 1 || ch == 2)//numeric searches
    {
        numSearch = atoi(search);
        if(numSearch == 0 && search[0] != '0')//checking for numeric input
        {
            printf("invalid input\n");
            return 0;
        }
    }
    res = fibSearch(0 , len - 1, ch , search , numSearch);//fibonacci search
    return res;
    
}

int main(int argc , char *argv[])//mainfunction
{
    int ch1 = 0; // choice of field
    int ch2 = 0; // choice of algorithm
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

    int res = 0;
    input(len);

    if(ch2 == 1)
        res = linearSearch(ch1 , search , len);
    if(ch2 == 2)
        res = binaryDriver(ch1 , search , len);
    if(ch2 == 3)
        res = fibonacciDriver(ch1 , search , len);

    if(res)
        printf("Element(s) found\n");
    else
        printf("Element not found\n");
    return 0;
}