#pragma once

typedef unsigned short ushort;

typedef struct matrix
{
	void **data;
	ushort rows, cols;
}matrix;

matrix mcreatef(ushort rows, ushort cols);
void mfree(matrix *m);
void print_matrix(matrix *m);