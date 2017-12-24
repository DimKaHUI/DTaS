#define _CRT_SECURE_NO_WARNINGS

#include "lgraph.h"
#include <stdlib.h>
#include <stdio.h>

int setup_lgraph(lgraph *g, int nodes_count)
{
	g->size = nodes_count;
	g->nodes = malloc(sizeof(node_t*));
	for (int i = 0; i < nodes_count; i++)
	{
		int len = 0;
		printf("Input number of %d's neightbours: ", i + 1);
		if (scanf("%d", &len) != 1)
			return ERROR_IO;
		g->nodes[i] = malloc(sizeof(node_t));
		node_t *head = g->nodes[i];
		head->v = i;
		head->visited = 0;
		for (int k = 0; k < len; k++)
		{
			head->next = malloc(sizeof(node_t));
			head = head->next;
			printf("Input neighbour: ");
			if (scanf("%d", &head->v) != 1 || head->v < 0 || head->v > nodes_count)
				return ERROR_IO;
			if (head->v < 1 || head->v > nodes_count)
				return ERROR_IO;
			head->v -= 1;
			head->visited = 0;
		}
		head->next = NULL;
	}

	printf("Graph data: \n");
	for (int i = 0; i < nodes_count; i++)
	{
		node_t *head = g->nodes[i];
		while (head)
		{
			printf("%d ", head->v + 1);
			if (head->next)
				printf(" -> ");
			head = head->next;
		}
		printf("\n");
	}

	return 0;
}


void m_reach(lgraph *graph, int v)
{
	if (graph == NULL || graph->nodes[v]->visited)
	{
		return;
	}	
	graph->nodes[v]->visited = 1;
	node_t *head = graph->nodes[v];
	head = head->next;
	while (head)
	{
		m_reach(graph, head->v);
		head = head->next;
	}	
}

void m_reachable(lgraph *graph, int v)
{
	printf("Nodes, not reachable from %d: ", v + 1);
	m_reach(graph, v);

	for (int i = 0; i < graph->size; i++)
	{
		if (graph->nodes[i]->visited == 0 && i != v)
		{
			printf("%d ", i + 1);
		}
	}
	printf("\n");
}

