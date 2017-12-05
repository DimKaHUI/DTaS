#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "sparsematrix.h"
#include <conio.h>
#include <time.h>

#define SIZE_X 1000
#define SIZE_Y 1000

#define ERROR_UNKNOWN_CMD -111
#define ERROR_ILLEGAL_SYMBOL -121

int main(void)
{
	srand(time(NULL));
	int command;
	int err = 0;
	printf("1. Summ of random matrixes %d x %d\n", SIZE_X, SIZE_Y);
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
			printf("Input matrix size, splitting with space: ");
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
			printf("Input matrix rows, cols and concentration, splitting with space: ");
			ulong rows, cols;
			float conc;
			if (scanf("%llu %llu %f", &rows, &cols, &conc) != 3)
			{
				err = ERROR_ILLEGAL_SYMBOL;
			}
			else
			{				
				matrix a = mrandom(rows, cols, conc);
				matrix b = mrandom(rows, cols, conc);
				printf("First: \n");
				print_matrix(&a);
				printf("Second: \n");
				print_matrix(&b);
				smatrix sa, sb;
				m2s(&a, &sa);
				m2s(&b, &sb);
				ssumm(&sa, &sb);
				printf("Result: \n");
				print_sparse(&sa);
				print_sparse_structure(&sa);
			}
		}
		else if (command == 2)
		{
			printf("Input matrix rows and cols, splitting with space: ");
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

				printf("\nInsides: \n");
				print_sparse_structure(&sa);

				ssumm(&sa, &sb);
				printf("\nResult: \n");
				print_sparse(&sa);
				printf("\nInsides: \n");
				print_sparse_structure(&sa);
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