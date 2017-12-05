#include "sparsematrix.h"


int mcreate(smatrix *m, ulong not_nill_count, ulong lines, ulong columns)
{
	try
	{
		m->A = new float[not_nill_count];
		m->LJ = new ulong[not_nill_count];
		m->LI = new ulong[lines];
	}
	catch (...)
	{
		return ERROR_ALLOCATION;
	}
	return 0;
}


void mdestroy(smatrix* m)
{
	delete[] m->A;
	delete[] m->LI;
	delete[] m->LJ;
}


float mget(smatrix* matrix, ulong line, ulong column)
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


ulong get_row(smatrix* a, ulong index)
{
	ulong res = 0;
	for ( ; ; res++)
	if (a->LI[res] > index)
		return res - 1;
}


float *arrexpand(float *arr, ulong len, ulong new_len)
{
	float *n = new float[new_len];
	for (ulong i = 0; i < len; i++)
		n[i] = arr[i];
	delete[] arr;
	return n;
}

void msumm(smatrix* a, const smatrix* b)
{

}


void msumm_simple(matrix* a, const matrix* b)
{
	for (ulong i = 0; i < a->rows; i++)
	for (ulong j = 0; j < a->cols; j++)
		a->data[i][j] = a->data[i][j] + b->data[i][j];
}
