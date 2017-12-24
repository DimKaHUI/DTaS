#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "locale.h"
#include <conio.h>

typedef struct graph
{
	int **link_matrix;
	int *visited;
	int nodes_count;
}graph;

graph *setup_graph(int nodes_count)
{
	graph *graph = malloc(sizeof(graph));
	graph->link_matrix = malloc(sizeof(float*));
	for (int i = 0; i < nodes_count; i++)
		graph->link_matrix[i] = malloc(sizeof(float) * nodes_count);
	graph->visited = malloc(sizeof(int)* nodes_count);

	// Инициализация матрицы связей
	int temp;
	for (int i = 0; i < nodes_count; i++)
	{
		for (int j = 0; j < nodes_count; j++)
		{
			if (i == j)
			{
				graph->link_matrix[i][j] = 0;
				continue;
			}
			printf("Input reachability from %d to %d: ", i + 1, j + 1);
			scanf("%d", &temp);
			if (temp != 0)
				graph->link_matrix[i][j] = 1;
			else
				graph->link_matrix[i][j] = 0;
		}
	}

	for (int i = 0; i < nodes_count; i++)
	{
		for (int j = 0; j < nodes_count; j++)
		{
			printf("%d ", graph->link_matrix[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < nodes_count; i++)
		graph->visited[i] = 0;
	graph->nodes_count = nodes_count;
	return graph;
}

void reset_visited(graph *graph)
{
	for (int i = 0; i < graph->nodes_count; i++)
		graph->visited[i] = 1;
}

void Reach(graph *graph, int v)
{
	graph->visited[v] = 0;
	for (int u = 0; u < graph->nodes_count; u++)
	{
		if (graph->link_matrix[v][u] != 0 && graph->visited[u])
			Reach(graph, u);
	}
}

void Reachable(graph *graph, int v)
{
	reset_visited(graph);
	printf("Nodes, not reachable from %d: ", v + 1);
	Reach(graph, v);
	for (int i = 0; i < graph->nodes_count; i++)
	{
		if (graph->visited[i] == 1 && i != v)
		{
			printf("%d ", i + 1);
		}
	}
	printf("\n");
}

int main()
{
	int size, node;
	printf("Input amount of nodes: ");
	if (scanf("%d", &size) != 1)
	{
		printf("Illegal symbol!\n");
		return -1;
	}
	if (size <= 0)
	{
		printf("Count of nodes must be bigger than zero\n");
		return -1;
	}
	printf("Input node number to find, which nodes are unreachable from it: ");
	if (scanf("%d", &node) != 1)
	{
		printf("Illegal symbol!\n");
		return -1;
	}
	if (node < 1 || node > size)
	{
		printf("Node number must be inside [1, %d]\n", size);
		return -1;
	}
	struct graph *g = setup_graph(size);
	Reachable(g, node - 1);
	_getch();
}
