#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int basen(int num , int base , char res[] , int i)//converts a decimal number to the specified base
{
    if(num == 0)
    {
        res[i++] = 0;
        return 0;
    }
    res[i++] = num%base; 
    basen(num/base , base , res , i);
}

void initialize(char arr[] , int len)
{
    for(int i = 0; i < len ;i++)
        arr[i] = 0;
}

double reliability(int n , int maxcost , int cost[] , double rely[])//returns the max reliability under the cost constraints
{
    int mincost,maxparalleldevices,netcost,i,j;
    mincost = maxparalleldevices = netcost = i = j = 0;

    for(i = 0 ; i < n; i++)//finding minimum cost
        mincost += cost[i];
    for(i = 0 ; i < n ; i++)//generating the maximum number of devices in parallel for table generation
        maxparalleldevices = maxparalleldevices > 1 + ((maxcost - mincost)/cost[i]) ?maxparalleldevices : 1 + ((maxcost - mincost)/cost[i]);
    
    double tableR [n][maxparalleldevices + 1];
    int tableC [n][maxparalleldevices + 1];
    for(i = 0 ; i < n ; i++)
        for(j = 0 ; j < n + 1 ; j++)
            tableR[i][j] = tableC[i][j] = 0;//initialization

    for(i = 0 ; i < n ; i++)//generating max parallel devices for individual stages
        tableR[i][0] = 1 + ((maxcost - mincost)/cost[i]);
    
    for(i = 0 ; i < n ; i++)
        for(int j = 1 ; j <= tableR[i][0] ; j++)
        {
            tableR[i][j] = 1.0 - pow((1.0 - rely[i]),j);//reliability computation for each parallel combination for each stage
            tableC[i][j] = cost[i]*j;//cost computation
        }

    int count,tempcost;//counter,equivalent base counter, temporary cost
    count = tempcost = 0;
    double maxrely,temprely;//max reliability, temporary reliability
    maxrely = 0;
    temprely = 1;
    char based[n];
    initialize(based , n);

    while(count < (int)pow(maxparalleldevices,n))//max count for stage combinations
    {
        temprely = 1;
        tempcost = 0;
        basen(count , maxparalleldevices , based , 0);//this logic is explained in README.txt
        for(int i = 0 ; i < n ; i++)//extracting single stage combination
        {
            temprely *= tableR[i][based[i] + 1];
            tempcost += tableC[i][based[i] + 1];
        }
        if(tempcost <= maxcost)
            if(temprely > maxrely && temprely != 1)
                maxrely = temprely;
        count++;
        initialize(based , n);
    }
    return maxrely;
}

int main(int argc , char *argv[])
{
    if(argc < 3)
    {
        printf("invalid\n");
        return 0;
    }
    int n,maxcost;
    n = atoi(argv[1]);
    maxcost = atoi(argv[2]);
    if(argc != 3 + 2*n) // total number of arguments
    {
        printf("invalid\n");
        return 0;
    }
    int cost[n];
    double rely[n];
    for(int i = 0 ; i < n ; i++)
    {
        cost[i] = atoi(argv[3 + i]);
        rely[i] = atof(argv[3 + n + i]);
    }

    printf("%0.3lf\n",reliability(n , maxcost , cost , rely));
    return 0;
}