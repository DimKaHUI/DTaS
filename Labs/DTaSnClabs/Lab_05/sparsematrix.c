#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "sparsematrix.h"

#define RAND01 (float)rand() / RAND_MAX
#define RAND(min, max) (max - min) * RAND01 + min
#define EPS 0.01

float mget(const smatrix* matrix, uint line, uint column)
{
	float value = 0;
	//ulong N1 = matrix->LI[line];
	uint N1 = getval(matrix->LI, line);
	uint N2 = getval(matrix->LI, line + 1);
	for (uint k = N1; k < N2; k++)
	{		
		if (matrix->LJ[k] == column)
		{
			value = matrix->A[k];
			break;
		}
	}
	return value;
}

uint getval(node_t* head, uint ind)
{
	if (head == NULL)
		return 0;
	for (uint i = 0; i < ind && head; i++)
	{
		head = head->next;
	}
	if (head == NULL)
		return 0;
	return head->n;
}

void setval(node_t* head, uint ind, uint val)
{
	for (uint i = 0; i < ind; i++)
	{
		head = head->next;
	}
	head->n = val;
}

void msumm(matrix* a, const matrix* b)
{
	for (uint i = 0; i < a->rows; i++)
	for (uint j = 0; j < a->cols; j++)
		a->data[i][j] = a->data[i][j] + b->data[i][j];
}

int msummres(const matrix* a, const matrix* b, matrix* res)
{
	res->cols = a->cols;
	res->rows = a->rows;
	res->data = malloc(sizeof(float*)* res->rows);
	if (res->data == NULL)
		return ERROR_ALLOCATION;
	for (uint i = 0; i < res->rows; i++)
	{
		res->data[i] = malloc(sizeof(float)* res->cols);
		if (res->data[i] == NULL)
			return ERROR_ALLOCATION;
	}

	for (uint i = 0; i < res->rows; i++)
	for (uint j = 0; j < res->cols; j++)
	{
		res->data[i][j] = a->data[i][j] + b->data[i][j];
	}
	return 0;
}

int read_matrix(matrix* a)
{
	printf("Input matrix: \n");
	// Memory allocation
	a->data = malloc(sizeof(float*)* a->rows);
	if (a->data == NULL)
		return ERROR_ALLOCATION;
	for (uint i = 0; i < a->rows; i++)
	{
		a->data[i] = malloc(sizeof(float)* a->cols);
		if (a->data[i] == NULL)
			return ERROR_ALLOCATION;
	}

	for (uint i = 0; i < a->rows; i++)
	for (uint j = 0; j < a->cols; j++)
	{
		printf("(%u, %u): ", i + 1, j + 1);
		float res;
		if (scanf("%f", &res) != 1)
			return ERROR_IO;
		a->data[i][j] = res;
	}
	return 0;
}

int read_zero_excluding(matrix* a)
{
	uint count;
	uint x, y;
	float value;
	printf("Input number of not-nill elements: \n");
	if (scanf("%u", &count) != 1)
		return ERROR_IO;
	a->data = malloc(sizeof(float*)* a->rows);
	if (a->data == NULL)
		return ERROR_ALLOCATION;
	for (uint i = 0; i < a->rows; i++)
	{
		a->data[i] = malloc(sizeof(float)* a->cols);
		if (a->data[i] == NULL)
			return ERROR_ALLOCATION;
	}
	for (uint i = 0; i < a->rows; i++)
	for (uint j = 0; j < a->cols; j++)
	{		
		a->data[i][j] = 0;
	}

	printf("Input points:\n");
	for (uint k = 0; k < count; k++)
	{
		printf("Line: ");
		if (scanf("%u", &x) != 1)
			return ERROR_IO;
		printf("Column: ");
		if (scanf("%u", &y) != 1)
			return ERROR_IO;
		printf("Value: ");
		if (scanf("%f", &value) != 1)
			return ERROR_IO;
		if (x >= a->rows || y >= a->cols)
		{
			return ERROR_OUT_OF_RANGE;
		}
		a->data[x][y] = value;
	}
	return 0;
}

void free_matrix(matrix* a)
{
	for (uint i = 0; i < a->rows; i++)
		free(a->data[i]);
	free(a->data);
}

void print_matrix(const matrix* m)
{
	for (uint i = 0; i < m->rows; i++)
	{
		for (uint j = 0; j < m->cols; j++)
		{
			if (fabs(m->data[i][j]) > EPS)
				printf("%+3.2f ", m->data[i][j]);
			else
				printf("##### ");
		}
		printf("\n");
	}
	
}

matrix mrandom(uint x, uint y, float concentration)
{	
	matrix a;
	a.rows = x;
	a.cols = y;
	a.data = malloc(sizeof(float*)* a.rows);
	if (a.data == NULL)
		return a;
	for (uint i = 0; i < a.rows; i++)
	{
		a.data[i] = malloc(sizeof(float)* a.cols);
		if (a.data[i] == NULL)
			return a;
	}

	for (uint i = 0; i < a.rows; i++)
	for (uint j = 0; j < a.cols; j++)
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
	for (uint i = 0; i < a->rows; i++)
	for (uint j = 0; j < a->cols; j++)
	if (a->data[i][j] != b->data[i][j])
	{
		//printf("Comparison failed on checking (%u, %u): %3.2f ~ %3.2f\n", i, j, a->data[i][j], b->data[i][j]);
		return 0;
	}
	return 1;
}

void m2s(const matrix* m, smatrix* s)
{
	s->rows = m->rows;
	s->cols = m->cols;
	s->LI = malloc(sizeof(uint)* m->rows);
	uint count = 0;
	uint rows = 0;
	uint prev_row = -1;
	for (uint i = 0; i < m->rows; i++)
	for (uint j = 0; j < m->cols; j++)
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
	{
		s->A = NULL;
		s->LJ = NULL;
		s->LI = malloc(sizeof(uint));
		s->LI->n = 0;
		s->LI->next = NULL;
		s->a_len = 0;
		return;
	}

	s->A = malloc(sizeof(float)* count);
	s->LJ = malloc(sizeof(uint) * count);
	//s->LI = malloc(sizeof(ulong)* (m->rows + 1));
	s->LI = malloc(sizeof(node_t));
	node_t *n = s->LI;
	for (uint i = 0; i < m->rows + 1; i++)
	{
		n->next = malloc(sizeof(node_t));
		n = n->next;
	}
	n->next = NULL;

	//s->LI[m->rows] = count;
	setval(s->LI, m->rows, count);
	uint pos_a = count;	
	for (uint i = m->rows - 1; ; i--)
	{
		int flag = 0;
		for (uint j = m->cols - 1; ; j--)
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
				//s->LI[i] = pos_a;
				setval(s->LI, i, pos_a);
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
	for (uint i = 0; i < s->rows; i++)
	{
		m->data[i] = malloc(sizeof(float)* s->cols);
		if (m->data[i] == NULL)
			return ERROR_ALLOCATION;
	}
	for (uint i = 0; i < s->rows; i++)
	for (uint j = 0; j < s->cols; j++)
	{
		m->data[i][j] = mget(s, i, j);
	}
	m->rows = s->rows;
	m->cols = s->cols;
	return 0;
}

void print_sparse(const smatrix* m)
{
	for (uint i = 0; i < m->rows; i++)
	{
		for (uint j = 0; j < m->cols; j++)
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
	uint count = 0;
	uint rows = 0;
	uint prev_row = -1;
	for (uint i = 0; i < m->rows; i++)
	for (uint j = 0; j < m->cols; j++)
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
	for (uint i = 0; i < m->a_len; i++)
		printf("%+3.3f ", m->A[i]);
	printf("\nLJ: ");
	for (uint i = 0; i < m->a_len; i++)
		printf("%6.6u ", m->LJ[i]);
	printf("\nLI: ");
	//for (ulong i = 0; i < m->rows + 1; i++)
		//printf("%4.4u ", m->LI[i]);
	node_t *node = m->LI;
	while (node && node->next)
	{
		printf("%6.6u ", node->n);
		node = node->next;
	}
	printf("\n");
}

void free_sparce(smatrix* a)
{
	free(a->A);
	free(a->LI);
	free(a->LJ);
}

uint getrow(const smatrix *s, uint index)
{
	for (uint i = s->rows; i >= 0; i--)
	{
		//if (s->LI[i] <= index)
		if (getval(s->LI, i) <= index)
			return i;
		if (i == 0)
			break;
	}
	return 0;
}
uint getcol(const smatrix *s, uint index)
{
	return s->LJ[index];
}

void printaf(float* arr, uint n)
{
	for (uint i = 0; i < n; i++)
		printf("%+3.2f ", arr[i]);
	printf("\n");
}
void printal(uint* arr, uint n)
{
	for (uint i = 0; i < n; i++)
		printf("%5.1u ", arr[i]);
	printf("\n");
}

int ssumm(smatrix* a, const smatrix* b)
{
	return 0;
}

int ssummres(const smatrix* a, const smatrix* b, smatrix* res)
{
	res->cols = a->cols;
	res->rows = a->rows;
	uint res_len = a->a_len + b->a_len;
	res->A = malloc(res_len * sizeof(uint));
	res->LJ = malloc(res_len * sizeof(uint));
	
	/*res->LI = malloc(sizeof(node_t));
	node_t *node = res->LI;
	for (uint i = 0; i < a->rows + 1; i++)
	{
		node->next = malloc(sizeof(node_t));
		node = node->next;
	}
	node->next = NULL;	
	*/

	uint a_pos = 0, b_pos = 0;
	node_t *anode = a->LI;
	node_t *bnode = b->LI;
	node_t *resnode = res->LI;
	uint a_row = 0, b_row = 0;
	while (anode && anode->n < a_pos)
	{
		a_row++;
		anode = anode->next;
	}
	while (bnode && bnode->n < b_pos)
	{
		b_row++;
		bnode = bnode->next;
	}
	if (anode)
	{
		anode = anode->next;
	}
	if (bnode)
	{
		bnode = bnode->next;
	}
	//uint A2 = anode->n;
	uint A2 = 0, B2 = 0;
	if (anode)
	{
		A2 = anode->n;
	}
	if (bnode)
	{
		B2 = bnode->n;
	}
	uint res_pos = 0;
	for (uint i = 0; i < res->rows; i++)
	{		
		//printf("I: %u, a_row: %u, A2: %u, a_pos: %u, b_row: %u, b_pos: %u\n", i, a_row, A2, a_pos, b_row, b_pos);
		
		resnode->n = res_pos;
		resnode = resnode->next;

		if (a_row == i && b_row == i)
		{
			while (a->LJ && b->LJ && b->LJ[b_pos] < a->LJ[b_pos] && b_pos < B2)
			{
				res->A[res_pos] = b->A[b_pos];
				res->LJ[res_pos] = b->LJ[b_pos];
				res_pos++;
				b_pos++;
			}
			while (a_pos < A2)
			{
				if (a->LJ && b->LJ && a->LJ[a_pos] == b->LJ[b_pos] && b_pos < B2)
				{
					float tmp = a->A[a_pos] + b->A[b_pos];					
					if (fabs(tmp) >= EPS)
					{
						res->A[res_pos] = tmp;
						res->LJ[res_pos] = a->LJ[a_pos];
						res_pos++;						
					}
					a_pos++;
					b_pos++;
				}
				else if (a->LJ)
				{
					res->A[res_pos] = a->A[a_pos];
					res->LJ[res_pos] = a->LJ[a_pos];
					res_pos++;
					a_pos++;
				}
			}
			while (b_pos < B2)
			{
				res->A[res_pos] = b->A[b_pos];
				res->LJ[res_pos] = b->LJ[b_pos];
				res_pos++;
				b_pos++;
			}
		}
		if (a_row == i && b_row != i)
		{
			while (a_pos < A2)
			{
				res->A[res_pos] = a->A[a_pos];
				res->LJ[res_pos] = a->LJ[a_pos];
				res_pos++;
				a_pos++;
			}
		}
		if (a_row != i && b_row == i)
		{
			while (b_pos < B2)
			{
				res->A[res_pos] = b->A[b_pos];
				res->LJ[res_pos] = b->LJ[b_pos];
				res_pos++;
				b_pos++;
			}
		}

		if (a_pos >= A2)
		{
			uint old_a2 = A2;
			while (old_a2 == A2 && anode)
			{
				anode = anode->next;
				if (anode)
				{
					A2 = anode->n;
					a_row++;
				}
			}
		}
		if (b_pos >= B2)
		{
			uint old_b2 = B2;
			while (old_b2 == B2 && bnode)
			{
				bnode = bnode->next;
				if (bnode)
				{
					B2 = bnode->n;
					b_row++;
				}
			}
		}		
	}
	resnode->n = res_pos;
	res->a_len = res_pos;
	return 0;
}


