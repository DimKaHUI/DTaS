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
			if (fabs(m->data[i][j]) > EPS)
				printf("%+3.2f ", m->data[i][j]);
			else
				printf("##### ");
		}
		printf("\n");
	}
	
}

matrix mrandom(ulong x, ulong y, float concentration)
{	
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

int mequal(const matrix* a, const matrix* b)
{
	if (a->rows != b->rows)
		return 0;
	if (a->cols != b->cols)
		return 0;
	for (ulong i = 0; i < a->rows; i++)
	for (ulong j = 0; j < a->cols; j++)
	if (a->data[i][j] != b->data[i][j])
	{
		//printf("Comparison failed on checking (%llu, %llu): %3.2f ~ %3.2f\n", i, j, a->data[i][j], b->data[i][j]);
		return 0;
	}
	return 1;
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

int s2m(const smatrix* s, matrix* m)
{
	m->data = malloc(sizeof(float*)* s->rows);
	if (m->data == NULL)
		return ERROR_ALLOCATION;
	for (ulong i = 0; i < s->rows; i++)
	{
		m->data[i] = malloc(sizeof(float)* s->cols);
		if (m->data[i] == NULL)
			return ERROR_ALLOCATION;
	}
	for (ulong i = 0; i < s->rows; i++)
	for (ulong j = 0; j < s->cols; j++)
	{
		m->data[i][j] = mget(s, i, j);
	}
	m->rows = s->rows;
	m->cols = s->cols;
	return 0;
}

void print_sparse(const smatrix* m)
{
	for (ulong i = 0; i < m->rows; i++)
	{
		for (ulong j = 0; j < m->cols; j++)
		{
			if (fabs(mget(m, i, j)) > EPS)
				printf("%+3.2f ", mget(m, i, j));
			else
				printf("##### ");
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
	printf("\n");
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
		if (s->LI[i] <= index)
			return i;
		if (i == 0)
			break;
	}
	return 0;
}
ulong getcol(const smatrix *s, ulong index)
{
	return s->LJ[index];
}

void printaf(float* arr, ulong n)
{
	for (ulong i = 0; i < n; i++)
		printf("%+3.2f ", arr[i]);
	printf("\n");
}
void printal(ulong* arr, ulong n)
{
	for (ulong i = 0; i < n; i++)
		printf("%5.1llu ", arr[i]);
	printf("\n");
}

ulong count_adds(smatrix *a, const smatrix *b)
{
	ulong res = 0;
	for (ulong i = 0; i < b->a_len; i++)
	{
		ulong row = getrow(b, i);
		ulong col = getcol(b, i);
		float aval = mget(a, row, col);
		if (fabs(aval) <= EPS)
			res++;
	}
	return res;
}

int ssumm(smatrix* a, const smatrix* b)
{
	ulong memshift = 0;
	for (ulong i = 0; i < a->a_len; i++)
	{
		ulong row = getrow(a, i);
		ulong col = getcol(a, i);		
		float bval = mget(b, row, col);
		a->A[i] += bval;
		
		if (fabs(a->A[i]) <= EPS) //Is zero now
		{
			for (ulong k = i; k < a->a_len; k++)
			{
				a->A[k] = a->A[k + 1];
				a->LJ[k] = a->LJ[k + 1];
			}			
			a->a_len--;
			memshift++;
			for (ulong k = row + 1; k <= a->rows; k++)
				a->LI[k]--;
			i--;
		}
	}
	
	ulong admem = count_adds(a, b);
	a->A = realloc(a->A, (a->a_len + admem - memshift) * sizeof(float));
	a->LJ = realloc(a->LJ, (a->a_len + admem - memshift) * sizeof(ulong));

	for (ulong i = 0; i < b->a_len; i++)
	{
		ulong row = getrow(b, i);
		ulong col = getcol(b, i);
		float aval = mget(a, row, col);
		if (fabs(aval) <= EPS)
		{
			//print_sparse_structure(a);
			ulong inspos = a->LI[row];
			for (; a->LJ[inspos] < col && inspos < a->LI[row + 1]; inspos++);
			//inspos--;

			a->a_len++;
		
			for (ulong k = a->a_len - 1; k >= inspos; k--)
			{
				a->A[k] = a->A[k - 1];
				a->LJ[k] = a->LJ[k - 1];
				if (k == 0)
					break;
			}			

			for (ulong k = row + 1; k <= a->rows; k++)
				a->LI[k]++;
			a->A[inspos] = b->A[i];
			a->LJ[inspos] = col;

			//print_sparse_structure(a);
		}
	}
	return 0;
}
