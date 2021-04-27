#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int len = 0;

int mindistance(int dist[], int sptSet[])//minimum vertex from set of vertices not part of spanning tree
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < len; v++)
	{
		if (sptSet[v] == 0 && dist[v] <= min)
		{
			min = dist[v];
			min_index = v;
		}
	}

	return min_index;
}

void printMatrix(int cost[len][len])//prints adjacency/cost matrix
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

void printsol(int dist[])
{
	printf("Vertex \t\t Distance from Source\n");
	for (int i = 0; i < len; i++)
		printf("%d \t\t %d\n", i, dist[i]);
}

void ssp(int graph[len][len], int src)//function to generate set of shortest paths
{
	int dist[len];//distance from source vertex 

	int sptSet[len];//to check if vertex is part of spanning tree

	for (int i = 0; i < len; i++)
    {
		dist[i] = INT_MAX;//infinity
        sptSet[i] = 0;
    }

	dist[src] = 0;//distance to same vertex is 0

	for (int i = 0; i < len - 1; i++) 
    {
		int u = mindistance(dist, sptSet);
		sptSet[u] = 1;

		for (int v = 0; v < len; v++)
		{
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
			//adjacent vertex to minimum distance vertex
				dist[v] = dist[u] + graph[u][v];
		}
	}
	printsol(dist);
}

int main(int argc , char * argv[])//driver
{
	if(argc <= 2)
	{
		printf("Invalid input\n");
		return 0;
	}

	len = atoi(argv[1]);

	if(argc < 2 + len*len)
	{
		printf("Invalid input\n");
		return 0;
	}

	int cost[len][len];

	for(int i = 0; i < len ;i ++)
		for(int j = 0 ; j < len ; j++)
			cost[i][j] = atoi(argv[2	 + i*len + j]);

	printMatrix(cost);

	for(int s = 0 ; s < len ; s++)
	{
		printf("----------------\n");
		ssp(cost, s);
	}

	return 0;
}
