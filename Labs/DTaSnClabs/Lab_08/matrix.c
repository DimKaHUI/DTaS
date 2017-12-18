#pragma once

#include <stdlib.h>
#include "matrix.h"
#include <stdio.h>

matrix mcreatef(ushort rows, ushort cols)
{
	matrix m;
	m.rows = rows;
	m.cols = cols;
	m.data = malloc(sizeof(float*)* rows);
	for (ushort i = 0; i < rows; i++)
	{
		m.data[i] = malloc(sizeof(float)* cols);
	}	
	return m;
}

void mfree(matrix* m)
{
	if (m == NULL || m->data == NULL)
		return;
	for (ushort i = 0; i < m->rows; i++)
	{
		free(m->data[i]);
	}
	free(m->data);
}

void print_matrix(matrix* m)
{	
	for (ushort i = 0; i <= m->cols; i++)
		printf("%3.3u ", i);
	printf("\n");
	for (ushort i = 0; i < m->rows; i++)
	{
		printf("%3.3u ", i);
		for (ushort j = 0; j < m->cols; j++)
			printf("%3.2f ", ((float**)m->data)[i][j]);
	}
	printf("\n");
}
