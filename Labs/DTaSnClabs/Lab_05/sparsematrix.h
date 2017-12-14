#pragma once

#include "stdexcpt.h"

// Error codes
#define ERROR_ALLOCATION -11
#define ERROR_IO -12
#define ERROR_OUT_OF_RANGE -13

typedef unsigned int uint;

typedef struct node_t
{
	uint n;
	struct node_t *next;
} node_t;

typedef struct smatrix // Sparse matrix
{
	float *A;          // Array of not nill elements
	uint *LJ;		   // Column indexes of not-nill elements from <an>
	node_t *LI;        // List of indexes of first not-nil element in each line
	uint rows;
	uint cols;
	uint a_len;
} smatrix;

typedef struct matrix
{
	float **data;
	uint rows;
	uint cols;
} matrix;

uint getval(node_t *head, uint ind);                 // Получение элемента списка по индексу
void setval(node_t *head, uint ind, uint val);	   // Запись в список по индексу

void msumm(matrix* a, const matrix* b);                // Simple algorithm, result: a = a + b;
int read_matrix(matrix *a);                            // Чтение матрицы из консоли
int read_zero_excluding(matrix *a);
void free_matrix(matrix *a);                           // Освобождение памяти, выделенной под матрицу
void print_matrix(const matrix *m);                    // Печать матрицы
matrix mrandom(uint x, uint y, float concentration); // Генерация случайной матрицы
int mequal(const matrix *a, const matrix *b);          // Проверка матриц на идентичность

void m2s(const matrix *m, smatrix *s);                 // Convertion of simple matrix to sparse matrix
int s2m(const smatrix *s, matrix *m);                  // Конвертация разреженной матрицы в обычную

void print_sparse(const smatrix *m);                   // Вывод разреженной матрицы в виде матрицы
void print_sparse_structure(const smatrix *m);         // Вывод разреженной матрицы в виде трех векторов
void free_sparce(smatrix *a);                          // Освобождение памяти, выделенной под разреженную матрицу
int ssumm(smatrix *a, const smatrix *b);               // Алгоритм сложения двух разреженных матриц

int msummres(const matrix *a, const matrix *b, matrix *res);
int ssummres(const smatrix *a, const smatrix *b, smatrix *res);