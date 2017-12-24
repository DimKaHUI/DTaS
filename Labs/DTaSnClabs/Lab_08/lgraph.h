#pragma once

#define ERROR_IO -112

typedef struct node_t
{
	int v;
	int visited;
	struct node_t *next;
}node_t;

typedef struct graph_list
{
	node_t **nodes;
	int size;
}lgraph;

int setup_lgraph(lgraph *g, int nodes_count);
void m_reachable(lgraph *graph, int v);
void mprint_graph(lgraph *g);