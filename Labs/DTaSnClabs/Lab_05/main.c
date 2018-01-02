#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "sparsematrix.h"
#include <conio.h>
#include <time.h>
#include <intrin.h>

#define ERROR_UNKNOWN_CMD -111
#define ERROR_ILLEGAL_SYMBOL -121

#pragma intrinsic(__rdtsc)
unsigned __int64 tick()
{
	return __rdtsc();
}

int main(void)
{
	srand(time(NULL));
	int command;
	int err = 0;
	printf("1. Summ of random matrixes\n");
	printf("2. Summ of manually created matrixes\n");
	printf("3. Test convertion\n");
	printf("4. Summ, zero matrixes excluding manually defined\n");
	//printf("5. Test another alorithm.\n");
	
	do
	{
		printf("\nInput command: ");
		fflush(stdin);
		if (scanf("%d", &command) != 1)
		{
			err = ERROR_ILLEGAL_SYMBOL;
			command = -1;
		}

		if (command == -1)
		{

		}
		if (command == 3)
		{
			printf("Input matrix size splitting with space: ");
			uint rows, cols;
			if (scanf("%u %u", &rows, &cols) != 2)
			{
				err = ERROR_ILLEGAL_SYMBOL;
			}
			else
			{				
				smatrix s;
				matrix m;
				m.rows = rows;
				m.cols = cols;
				err = read_matrix(&m);
				if (err == 0)
				{
					printf("Simple matrix: \n");
					print_matrix(&m);
					printf("Sparse matrix: \n");
					m2s(&m, &s);
					print_sparse(&s);
					printf("Sparse structure: \n");
					print_sparse_structure(&s);
				}
			}
		}
		else if (command == 1)
		{
			printf("Input matrix rows, cols, fullness and output flag (0 - no out, 1 - full, 2 - sparse only) splitting with space: \n");
			uint rows, cols;
			int flag;
			float conc;			
			if (scanf("%u %u %f %d", &rows, &cols, &conc, &flag) != 4)
			{
				err = ERROR_ILLEGAL_SYMBOL;
			}
			else
			{				
				matrix a = mrandom(rows, cols, conc);
				matrix b = mrandom(rows, cols, conc);
				matrix mres;
				if (flag == 1)
				{
					printf("\nFirst: \n");
					print_matrix(&a);
					printf("\nSecond: \n");
					print_matrix(&b);
				}				
				smatrix sa, sb, sres;
// TODO ERROR
				node_t *node;
				sres.LI = malloc(sizeof(node_t));
				node = sres.LI;
				for (uint i = 0; i < a.rows + 1; i++)
				{
					node->next = malloc(sizeof(node_t));
					node = node->next;
				}
				node->next = NULL;

				m2s(&a, &sa);
				m2s(&b, &sb);
				if (flag == 2)
				{
					printf("\nFirst: \n");
					print_sparse_structure(&sa);
					printf("\nSecond: \n");
					print_sparse_structure(&sb);
				}
				uint time_sparse = tick();
				ssummres(&sa, &sb, &sres);
				time_sparse = tick() - time_sparse;
				if (flag == 1)
				{
					printf("\nResult: \n");
					print_sparse(&sres);
					printf("\nInsides: \n");
					print_sparse_structure(&sres);
				}
				if (flag == 2)
				{
					printf("Resulting matrix:\n");
					print_sparse_structure(&sres);
				}
				uint time_simple = tick();
				msummres(&a, &b, &mres);
				time_simple = tick() - time_simple;

				printf("Time of simple summ: %u\n",  time_simple);
				printf("Time of sparse summ: %u\n", time_sparse);
				printf("Ratio (simple to sparse): %3.2f\n", (double)time_simple / time_sparse);
				uint spmem = (sizeof(float)+sizeof(uint)) * sa.a_len + sizeof(uint) * 2;
				node = sa.LI;
				while (node)
				{
					spmem += sizeof(node_t);
					node = node->next;
				}
				uint simplemem = sizeof(matrix) + sizeof(float)* (a.cols * a.rows - 1);
				printf("Memory of simple: %u\n", simplemem);
				printf("Memory of sparse: %u\n", spmem);

				printf("Memory ratio (simple to sparse): %3.2f\n", (double)simplemem / spmem);
			}
		}
		else if (command == 2)
		{
			printf("Input matrix rows and cols splitting with space: ");
			uint rows, cols;
			if (scanf("%u %u", &rows, &cols) != 2)
			{
				err = ERROR_ILLEGAL_SYMBOL;
			}
			else
			{
				matrix mres;
				printf("Inputting first matrix: \n");
				matrix a = {.rows = rows, .cols = cols};
				read_matrix(&a);
				printf("\nFirst matrix: \n");
				print_matrix(&a);
				printf("\nInputting second matrix: \n");
				matrix b = { .rows = rows, .cols = cols };
				read_matrix(&b);
				printf("\nSecond matrix: \n");
				print_matrix(&b);
				smatrix sa, sb, sres;

// TODO ERROR
				sres.LI = malloc(sizeof(node_t));
				node_t *node = sres.LI;
				for (uint i = 0; i < a.rows + 1; i++)
				{
					node->next = malloc(sizeof(node_t));
					node = node->next;
				}
				node->next = NULL;

				m2s(&a, &sa);
				m2s(&b, &sb);

				ssummres(&sa, &sb, &sres);
				printf("\nResult: \n");
				print_sparse(&sa);
				printf("\nInsides: \n");
				print_sparse_structure(&sa);

				msummres(&a, &b, &mres);
				printf("\nResult simple: \n");
				print_matrix(&mres);

				matrix result;
				s2m(&sa, &result);
				if (mequal(&a, &result))
				{
					printf("\nRESULTS ARE EQUAL!\n");
				}
				else
				{
					printf("\nRESULTS ARE NOT EQUAL!\n");
				}
			}
		}
		else if (command == 4)
		{
			printf("Input matrix rows and cols splitting with space: ");
			uint rows, cols;
			if (scanf("%u %u", &rows, &cols) != 2)
			{
				err = ERROR_ILLEGAL_SYMBOL;
			}
			else
			{
				printf("Inputting first matrix: \n");
				matrix a = { .rows = rows, .cols = cols };
				err = read_zero_excluding(&a);		
				if (err != 0)
				{
					goto errors;
				}
				printf("\nInputting second matrix: \n");
				matrix b = { .rows = rows, .cols = cols };
				err = read_zero_excluding(&b);	
				if (err != 0)
				{
					goto errors;
				}
				smatrix sa, sb, sres;
				matrix mres;

// TODO ERROR
				sres.LI = malloc(sizeof(node_t));
				node_t *node = sres.LI;
				for (uint i = 0; i < a.rows + 1; i++)
				{
					node->next = malloc(sizeof(node_t));
					node = node->next;
				}
				node->next = NULL;

				m2s(&a, &sa);
				m2s(&b, &sb);
				printf("\nFirst matrix: \n");
				print_sparse_structure(&sa);
				printf("\nSecond matrix: \n");
				print_sparse_structure(&sb);

				uint time_sparse = tick();
				ssummres(&sa, &sb, &sres);
				time_sparse = tick() - time_sparse;
				uint time_simple = tick();
				msummres(&a, &b, &mres);
				time_simple = tick() - time_simple;
				printf("\nResult: \n");
				print_sparse_structure(&sres);

				printf("\nTime of simple summ: %u\n", time_simple);
				printf("Time of sparse summ: %u\n", time_sparse);
				printf("Ratio (simple to sparse): %3.2f\n", (double)time_simple / time_sparse);
				uint spmem = (sizeof(float)+sizeof(uint)) * sa.a_len + sizeof(uint)* 2;
				node = sa.LI;
				while (node)
				{
					spmem += sizeof(node_t);
					node = node->next;
				}
				uint simplemem = sizeof(matrix)+sizeof(float)* (a.cols * a.rows - 1);
				printf("Memory of simple: %u\n", simplemem);
				printf("Memory of sparse: %u\n", spmem);
				printf("Memory ratio (simple to sparse): %3.2f\n", (double)simplemem / spmem);
			}
		}
		else if (command == 5)
		{
			uint rows = 5, cols = 5;
			if (scanf("%u %u", &rows, &cols) != 2)
			{
				err = ERROR_ILLEGAL_SYMBOL;
			}
			else
			{
				matrix a = { .rows = rows, .cols = cols };
				a = mrandom(rows, cols, 0.1f);
				if (err != 0)
				{
					goto errors;
				}
				matrix b = { .rows = rows, .cols = cols };
				b = mrandom(rows, cols, 0.1f);
				if (err != 0)
				{
					goto errors;
				}
				smatrix sa, sb, sres;
				m2s(&a, &sa);
				m2s(&b, &sb);
				printf("\nFirst matrix: \n");
				print_sparse(&sa);
				print_sparse_structure(&sa);
				printf("\nSecond matrix: \n");
				print_sparse(&sb);
				print_sparse_structure(&sb);

// TODO ERROR
				sres.LI = malloc(sizeof(node_t));
				node_t *node = sres.LI;
				for (uint i = 0; i < sa.rows + 1; i++)
				{
					node->next = malloc(sizeof(node_t));
					node = node->next;
				}
				node->next = NULL;

				uint time_sparse = tick();
				ssummres(&sa, &sb, &sres);
				time_sparse = tick() - time_sparse;
				matrix mres;
				uint time_simple = tick();				
				msummres(&a, &b, &mres);
				time_simple = tick() - time_simple;
				printf("\nResult: \n");
				print_sparse(&sres);
				print_sparse_structure(&sres);
				printf("Correct:\n");
				print_matrix(&mres);

				printf("\nTime of simple summ: %u\n", time_simple);
				printf("Time of sparse summ: %u\n", time_sparse);
				printf("Ratio (simple to sparse): %3.2f\n", (double)time_simple / time_sparse);
			}
		}
		else
			err = ERROR_UNKNOWN_CMD;

		// Error handling
		errors:
		switch (err)
		{
		case ERROR_ALLOCATION:
			printf("Allocation error!\n");
			break;
		case ERROR_ILLEGAL_SYMBOL:
			printf("Illegal symbol!\n");
			break;
		case ERROR_IO:
			printf("IO error\n");
			break;
		case ERROR_UNKNOWN_CMD:
			printf("Unknown command!\n");
			break;
		case ERROR_OUT_OF_RANGE:
			printf("Index was outside the size of matrix\n");
			break;
		}
	} while (command != 0);
}