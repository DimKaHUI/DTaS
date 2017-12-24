#define _CRT_SECURE_NO_WARNINGS

#include "mgraph.h"
#include <stdio.h>
#include <stdlib.h>

int setup_graph(graph *g, int nodes_count)
{
	g->link_matrix = malloc(sizeof(float*));
	for (int i = 0; i < nodes_count; i++)
		g->link_matrix[i] = malloc(sizeof(float)* nodes_count);
	g->visited = malloc(sizeof(int)* nodes_count);

	// Инициализация матрицы связей
	int temp;
	for (int i = 0; i < nodes_count; i++)
	{
		for (int j = 0; j < nodes_count; j++)
		{
			if (i == j)
			{
				g->link_matrix[i][j] = 0;
				continue;
			}
			printf("Input reachability from %d to %d: ", i + 1, j + 1);
			if (scanf("%d", &temp) != 1)
				return ERROR_IO;
			if (temp != 0)
				g->link_matrix[i][j] = 1;
			else
				g->link_matrix[i][j] = 0;
		}
	}

	for (int i = 0; i < nodes_count; i++)
	{
		for (int j = 0; j < nodes_count; j++)
		{
			printf("%d ", g->link_matrix[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < nodes_count; i++)
		g->visited[i] = 0;
	g->nodes_count = nodes_count;
	return 0;
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

void print_graph(graph *g)
{
	FILE *output = fopen("out.gv", "w");
	char letters[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
	fprintf(output, "digraph lab_08 {\n");
	for (int i = 0; i < g->nodes_count; i++)
	for (int j = 0; j < g->nodes_count; j++)
	{
		if (g->link_matrix[i][j])
		{
			fprintf(output, "%c -> %c\n", letters[i], letters[j]);
		}
	}
	fprintf(output, "}");
	fclose(output);
}
