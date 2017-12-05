#pragma once

#include "stdexcpt.h"

// Error codes
#define ERROR_ALLOCATION -11

typedef unsigned long long ulong;

struct smatrix
{
	float *A;        // Array of not nill elements
	ulong *LJ;   // Column indexes of not-nill elements from <an>
	ulong *LI;   // Array of indexes of first not-nil element in each line
};

struct matrix
{
	float **data;
	ulong rows;
	ulong cols;
};


int mcreate(smatrix *m, ulong not_nill_count, ulong lines, ulong columns);

void mdestroy(smatrix*); 

float mget(smatrix *matrix, ulong line, ulong column);

void msumm(smatrix* a, const smatrix* b);
void msumm_simple(matrix *a, const matrix *b);

smatrix m2s(matrix *src);

matrix s2m(smatrix *src);