#pragma once

#include "stdexcpt.h"

// Error codes
#define ERROR_ALLOCATION -11
#define ERROR_IO -12

typedef unsigned long long ulong;

typedef struct smatrix
{
	float *A;        // Array of not nill elements
	ulong *LJ;   // Column indexes of not-nill elements from <an>
	ulong *LI;   // Array of indexes of first not-nil element in each line
	ulong rows;
	ulong cols;
	ulong a_len;
} smatrix;

typedef struct matrix
{
	float **data;
	ulong rows;
	ulong cols;
} matrix;

void msumm(matrix* a, const matrix* b); // Simple algorithm, result: a = a + b;
int read_matrix(matrix *a);
void free_matrix(matrix *a);
void print_matrix(const matrix *m);
matrix mrandom(ulong x, ulong y, float concentration);
int mequal(const matrix *a, const matrix *b);

void m2s(const matrix *m, smatrix *s);         // Convertion of simple matrix to sparse matrix
int s2m(const smatrix *s, matrix *m);

void print_sparse(const smatrix *m);
void print_sparse_structure(const smatrix *m);
void free_sparce(smatrix *a);
int ssumm(smatrix *a, const smatrix *b);