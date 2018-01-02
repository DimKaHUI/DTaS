#pragma once

#define ERROR_IO -111

typedef struct graph
{
	int **link_matrix;
	int *visited;
	int nodes_count;
}graph;

int setup_graph(graph *graph, int nodes_count);
void Reachable(graph *graph, int v);
void print_graph(graph *g);