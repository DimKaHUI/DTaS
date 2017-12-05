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
			if (mget(m, i, j) != 0)
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
		printf("%3.2f ", arr[i]);
	printf("\n");
}
void printal(ulong* arr, ulong n)
{
	for (ulong i = 0; i < n; i++)
		printf("%llu ", arr[i]);
	printf("\n");
}

int ssumm(smatrix* a, const smatrix* b)
{
	for (ulong i = 0; i < a->a_len; i++)
	{
		ulong row = getrow(a, i);
		ulong col = getcol(a, i);
		printf("Row: %llu, Col: %llu\n", row + 1, col + 1);
		float bval = mget(b, row, col);
		a->A[i] += bval;
		
		if (fabs(a->A[i]) <= EPS) //Is zero now
		{
			printaf(a->A, a->a_len);
			for (ulong k = i; k < a->a_len; k++)
			{
				a->A[k] = a->A[k + 1];
				a->LJ[k] = a->LJ[k + 1];
			}
			a->a_len--;
			printaf(a->A, a->a_len);
			for (ulong k = row + 1; k <= a->rows; k++)
				a->LI[k]--;

			i--;
		}
	}
	
	/*for (ulong i = 0; i < b->a_len; i++)
	{
		ulong row = getrow(b, i);
		ulong col = getcol(b, i);
		float aval = mget(a, row, col);
		if (aval == 0)
		{
			// Inserting element
			ulong a_line_index = a->LI[row];
			ulong a_next_line_index = a->LI[row + 1];
			ulong insertion_pos = a_line_index;
			for (; insertion_pos < a_next_line_index && a->LJ[insertion_pos] < col; insertion_pos++);
			
			if (a_line_index == a_next_line_index) // This line is full-zero
			{
				printf("Zero line!\n");
			}
			else // This line is not fully zero
			{
				// Shifting
				a->a_len++;
				a->A = realloc(a->A, a->a_len * sizeof(float));
				a->LJ = realloc(a->LJ, a->a_len * sizeof(ulong));
				for (ulong k = a->a_len - 1; k >= insertion_pos; k--)
				{
					a->A[k] = a->A[k - 1];
					a->LJ[k] = a->LJ[k - 1];
					if (k == 0)
						break;
				}
				a->A[insertion_pos] = b->A[i];
				a->LJ[insertion_pos] = b->A[i];
			}

		}
	}*/
	
}
