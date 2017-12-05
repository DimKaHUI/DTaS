#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "sparsematrix.h"
#include <time.h>
#include <conio.h>

// time = (t2–t1)*t + t1
#define RAND01 (float)rand() / RAND_MAX
#define RAND(min, max) (max - min) * RAND01 + min
#define EPS 0.01

float mget(const smatrix* matrix, ulong line, ulong column)
{
	float value = 0;
	ulong N1 = matrix->LI[line];
	ulong N2 = matrix->LI[line + 1];
	for (ulong k = N1; k < N2; k++)
	{		
		if (matrix->LJ[k] == column)
		{
			value = matrix->A[k];
			break;
		}
	}
	return value;
}

void msumm(matrix* a, const matrix* b)
{
	for (ulong i = 0; i < a->rows; i++)
	for (ulong j = 0; j < a->cols; j++)
		a->data[i][j] = a->data[i][j] + b->data[i][j];
}

int read_matrix(matrix* a)
{
	printf("Input matrix: \n");
	// Memory allocation
	/*a->data = malloc(sizeof(float*) * a->rows + sizeof(float) * a->cols * a->rows);
	if (a->data == NULL)
		return ERROR_ALLOCATION;
	// Pointers
	for (ulong i = 0; i < a->rows; i++)
	{
		a->data[i] = (float*)a->data + sizeof(float*)* a->rows + sizeof(float)* i;
	}*/
	a->data = malloc(sizeof(float*)* a->rows);
	if (a->data == NULL)
		return ERROR_ALLOCATION;
	for (ulong i = 0; i < a->rows; i++)
	{
		a->data[i] = malloc(sizeof(float)* a->cols);
		if (a->data[i] == NULL)
			return ERROR_ALLOCATION;
	}

	for (ulong i = 0; i < a->rows; i++)
	for (ulong j = 0; j < a->cols; j++)
	{
		printf("(%llu, %llu): ", i + 1, j + 1);
		float res;
		if (scanf("%f", &res) != 1)
			return ERROR_IO;
		a->data[i][j] = res;
	}
	return 0;
}

void free_matrix(matrix* a)
{
	for (ulong i = 0; i < a->rows; i++)
		free(a->data[i]);
	free(a->data);
}

void print_matrix(const matrix* m)
{
	for (ulong i = 0; i < m->rows; i++)
	{
		for (ulong j = 0; j < m->cols; j++)
		{
			if (m->data[i][j] != 0)
				printf("%+3.2f ", m->data[i][j]);
			else
				printf("##### ");
		}
		printf("\n");
	}
	
}

matrix mrandom(ulong x, ulong y, float concentration)
{
	srand(time(NULL));
	matrix a;
	a.rows = x;
	a.cols = y;
	a.data = malloc(sizeof(float*)* a.rows);
	if (a.data == NULL)
		return a;
	for (ulong i = 0; i < a.rows; i++)
	{
		a.data[i] = malloc(sizeof(float)* a.cols);
		if (a.data[i] == NULL)
			return a;
	}

	for (ulong i = 0; i < a.rows; i++)
	for (ulong j = 0; j < a.cols; j++)
	{
		float chance = RAND01;
		if (concentration > chance)
			a.data[i][j] = RAND(-10, 10);
		else
			a.data[i][j] = 0;
	}
	return a;
}

void m2s(const matrix* m, smatrix* s)
{
	s->rows = m->rows;
	s->cols = m->cols;
	s->LI = malloc(sizeof(ulong)* m->rows);
	ulong count = 0;
	ulong rows = 0;
	ulong prev_row = -1;
	for (ulong i = 0; i < m->rows; i++)
	for (ulong j = 0; j < m->cols; j++)
	if (m->data[i][j] != 0)
	{
		count++;
		if (i != prev_row)
		{
			rows++;
			prev_row = i;
		}
	}	

	if (count == 0)
		return;

	s->A = malloc(sizeof(float)* count);
	s->LJ = malloc(sizeof(ulong) * count);
	s->LI = malloc(sizeof(ulong)* (m->rows + 1));

	printf("Count: %llu\n", count);
	s->LI[m->rows] = count;
	ulong pos_a = count;	
	for (ulong i = m->rows - 1; ; i--)
	{
		int flag = 0;
		for (ulong j = m->cols - 1; ; j--)
		{
			if (m->data[i][j] != 0)
			{
				flag = 1;
				pos_a--;
				s->A[pos_a] = m->data[i][j];
				s->LJ[pos_a] = j;				
			}
			if (j == 0)
			{
				s->LI[i] = pos_a;
				break;
			}			
		}
		if (i == 0)
			break;
	}	
	s->a_len = count;
}

void print_sparse(const smatrix* m)
{
	for (ulong i = 0; i < m->rows; i++)
	{
		for (ulong j = 0; j < m->cols; j++)
		{
			printf("%+3.2f ", mget(m, i, j));
		}
		printf("\n");
	}
}

void print_sparse_structure(const smatrix* m)
{
	ulong count = 0;
	ulong rows = 0;
	ulong prev_row = -1;
	for (ulong i = 0; i < m->rows; i++)
	for (ulong j = 0; j < m->cols; j++)
	if (mget(m, i, j) != 0)
	{
		count++;
		if (i != prev_row)
		{
			rows++;
			prev_row = i;
		}
	}

	printf(" A: ");
	for (ulong i = 0; i < count; i++)
		printf("%3.2f ", m->A[i]);
	printf("\nLJ: ");
	for (ulong i = 0; i < count; i++)
		printf("%4.4llu ", m->LJ[i]);
	printf("\nLI: ");
	for (ulong i = 0; i < m->rows + 1; i++)
		printf("%4.4llu ", m->LI[i]);
}

void free_sparce(smatrix* a)
{
	free(a->A);
	free(a->LI);
	free(a->LJ);
}

ulong getrow(const smatrix *s, ulong index)
{
	for (ulong i = s->rows; i >= 0; i--)
	{
		if (s->LI[i] < index)
			return i;
	}
	return -1;
}
ulong getcol(const smatrix *s, ulong index)
{
	return s->LJ[index];
}

int ssumm(smatrix* a, const smatrix* b)
{
	for (ulong i = 0; i < max(a->a_len, b->a_len); i++)
	{
		if (getrow(a, i) == getrow(b, i) && getcol(a, i) == getcol(b, i))
		{
			a->A[i] += b->A[i];
			if (fabs(a->A[i] - EPS) == 0) //Is zero now
			{
				// Deleting element
				for (ulong k = i; k < a->a_len - 1; k++)
				{
					a->A[k] = a->A[k + 1];
					a->LJ[k] = a->LJ[k + 1];
				}
				a->A = realloc(a->A, --a->a_len);
				a->LJ = realloc(a->LJ, a->a_len);

				// Handling lines
				for (ulong k = getrow(a, i); k < a->rows; k++)
					a->LI[k] = a->LI[k];
			}
		}
		else
		{
			ulong row = getrow(b, i); // Line of current element from b
			ulong col = getcol(b, i); // Column of current element from b
			ulong a_line_start = a->LI[row]; // Position of line from a
			// Inserting
			a->A = realloc(a->A, ++a->a_len);
			a->LJ = realloc(a->LJ, a->a_len);			
			for (ulong k = a->a_len - 1; k >= i; k--)
			{
				a->A[k] = a->A[k - 1];
				a->LJ[k] = a->LJ[k - 1];
			}
			a->A = realloc(a->A, ++a->a_len);
			a->LJ = realloc(a->LJ, a->a_len);
			a->A[i] = b->A[i];

			// Handling lines
			for (ulong k = i; k < a->rows; k++)
				a->LI[k] = a->LI[k];
		}
	}
}
