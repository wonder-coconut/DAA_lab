#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int len = 0;

int minDistance(int dist[], int sptSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < len; v++)
		if (sptSet[v] == 0 && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

void printMatrix(int cost[len][len])
{
	for(int i = 0 ; i < len ; i++)
	{
		for(int j = 0 ; j < len ; j++)
		{
			printf("%d ",cost[i][j]);
		}
		printf("\n");
	}
}

void printSolution(int dist[])
{
	printf("Vertex \t\t Distance from Source\n");
	for (int i = 0; i < len; i++)
		printf("%d \t\t %d\n", i, dist[i]);
}

void ssp(int graph[len][len], int src)
{
	int dist[len]; 

	int sptSet[len];

	for (int i = 0; i < len; i++)
    {
		dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

	dist[src] = 0;

	for (int count = 0; count < len - 1; count++) 
    {
		
		int u = minDistance(dist, sptSet);

		sptSet[u] = 1;

		for (int v = 0; v < len; v++)


			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}
	printSolution(dist);
}

int main(int argc , char * argv[])
{
	if(argc <= 3)
	{
		printf("Invalid input\n");
		return 0;
	}

	len = atoi(argv[1]);
	int s = atoi(argv[2]);

	if(argc < 3 + len*len)
	{
		printf("Invalid input\n");
		return 0;
	}

	int cost[len][len];

	for(int i = 0; i < len ;i ++)
		for(int j = 0 ; j < len ; j++)
			cost[i][j] = atoi(argv[3 + i*len + j]);

	printMatrix(cost);
	ssp(cost, s);

	return 0;
}
