#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "sparsematrix.h"
#include <conio.h>
#include <time.h>
#include <intrin.h>

#define SIZE_X 1000
#define SIZE_Y 1000

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
	printf("3. Test convertion");
	
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
			ulong rows, cols;
			if (scanf("%llu %llu", &rows, &cols) != 2)
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
			printf("Input matrix rows, cols, concentration and output flag (0 - false, not 0 - true) splitting with space: ");
			ulong rows, cols;
			int flag;
			float conc;			
			if (scanf("%llu %llu %f %d", &rows, &cols, &conc, &flag) != 4)
			{
				err = ERROR_ILLEGAL_SYMBOL;
			}
			else
			{				
				matrix a = mrandom(rows, cols, conc);
				matrix b = mrandom(rows, cols, conc);
				if (flag)
				{
					printf("\nFirst: \n");
					print_matrix(&a);
					printf("\nSecond: \n");
					print_matrix(&b);
				}
				smatrix sa, sb;
				m2s(&a, &sa);
				m2s(&b, &sb);
				ulong time_sparse = tick();
				ssumm(&sa, &sb);
				time_sparse = tick() - time_sparse;
				if (flag)
				{
					printf("\nResult: \n");
					print_sparse(&sa);
					printf("\nInsides: \n");
					print_sparse_structure(&sa);
				}
				ulong time_simple = tick();
				msumm(&a, &b);
				time_simple = tick() - time_simple;
				if (flag)
				{
					printf("\nResult simple: \n");
					print_matrix(&a);
				}

				printf("Time of simple summ: %llu\n",  time_simple);
				printf("Time of sparse summ: %llu\n", time_sparse);
				printf("Ratio (sparse to simple): %3.2f\n", (double)time_sparse / time_simple);
				ulong spmem = (sizeof(float)+sizeof(ulong)) * sa.a_len + sizeof(ulong)* sa.rows;
				ulong simplemem = sizeof(matrix) + sizeof(float)* (a.cols * a.rows - 1);
				printf("Memory of simple: %llu\n", simplemem);
				printf("Memory of sparse: %llu\n", spmem);
				printf("Memory ratio (simple to sparse): %3.2f\n", (double)simplemem / spmem);
			}
		}
		else if (command == 2)
		{
			printf("Input matrix rows and cols splitting with space: ");
			ulong rows, cols;
			if (scanf("%llu %llu", &rows, &cols) != 2)
			{
				err = ERROR_ILLEGAL_SYMBOL;
			}
			else
			{
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
				smatrix sa, sb;
				m2s(&a, &sa);
				m2s(&b, &sb);

				ssumm(&sa, &sb);
				printf("\nResult: \n");
				print_sparse(&sa);
				printf("\nInsides: \n");
				print_sparse_structure(&sa);

				msumm(&a, &b);
				printf("\nResult simple: \n");
				print_matrix(&a);

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
		else
			err = ERROR_UNKNOWN_CMD;

		// Error handling
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
		}
	} while (command != 0);
}