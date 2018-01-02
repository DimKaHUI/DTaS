#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "locale.h"
#include <conio.h>
#include "lgraph.h"
#include "mgraph.h"
#include <intrin.h>

#pragma intrinsic(__rdtsc)
unsigned __int64 tick()
{
	return __rdtsc();
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

	unsigned long long time_matrix, time_list, mmem, lmem;

	printf("Matrix-based graph: \n");
	struct graph g;
	setup_graph(&g, size);
	time_matrix = tick();
	Reachable(&g, node - 1);
	time_matrix = tick() - time_matrix;

	printf("List-based graph: \n");
	lgraph lgraph;
	setup_lgraph(&lgraph, size);
	time_list = tick();
	m_reachable(&lgraph, node - 1);
	time_list = tick() - time_list;
	print_graph(&g);

	mmem = sizeof(int)* size * size + sizeof(int)* size + sizeof(int);
	lmem = sizeof(int);
	for (int i = 0; i < size; i++)
	{
		node_t *head = lgraph.nodes[i];
		lmem += sizeof(node_t);
		while (head)
		{
			lmem += sizeof(node_t);
			head = head->next;
		}
	}

	printf("\nTime of matrix-based algorithm: %llu\n", time_matrix);
	printf("Time of list-based algorithm: %llu\n", time_list);
	printf("Ratio(list to algorithm: %3.2f\n", (double)time_list / (double)time_matrix);
	printf("Memory of matrix-based graph: %llu\n", mmem);
	printf("Memory of list-based graph: %llu\n", lmem);
	printf("Ratio(list to algorithm: %3.2f\n", (double)lmem / (double)mmem);
	printf("Finished!\n");
	_getch();
}
