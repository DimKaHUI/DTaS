#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "graph.h"
#include "matrix.h"
#include <stdio.h>
#include <math.h>

int read_graph(matrix *m)
{
	ushort Vlen;
	printf("Input amount of vertises: ");
	if (scanf("%u", &Vlen) != 1)
		return ERROR_IO;
	if (Vlen == 0)
		return ERROR_SIZES;
	*m = mcreatef(Vlen, Vlen);
	printf("Input edge weights. Minus one means, that edge does not exist.\n");
	for (ushort v = 0; v < Vlen; v++)
	{
		for (ushort p = 0; p < Vlen; p++)
		{
			if (p == v)
				continue;
			float edge;
			printf("Edge (%u, %u): ", v, p);
			if (scanf("%f", &edge) != 1)
				return ERROR_IO;
			if (edge < 0)
				((float**)m->data)[v][p] = -1.0f;
			else
				((float**)m->data)[v][p] = edge;
		}
	}
	return 0;
}

float longest_way(matrix* W)
{
	// Floyd–Warshall algorithm
	for (ushort k = 0; k < W->rows; k++)
	for (ushort i = 0; i < W->rows; i++)
	for (ushort j = 0; j < W->rows; j++)	
		((float**)W->data)[i][j] = fmax(((float**)W->data)[i][j], ((float**)W->data)[i][k] + ((float**)W->data)[k][j]);
	return 0;
}
