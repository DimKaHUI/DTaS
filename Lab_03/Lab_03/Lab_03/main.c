/* Монахов Дмитрий. ИУ7-34. Работа 3
 * 
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <intrin.h>
#include "stackarr.h"
#include "stacklist.h"

// Error codes
#define ERROR_UNRECOGNIZED_COMMAND -1
#define ERROR_INCORRECT_INPUT_SYMBOLS -2

#pragma intrinsic(__rdtsc)
void analize();

unsigned __int64 tick()
{
	return __rdtsc();
}

int main(void)
{
	printf("Stack\nPring number of menu element to proceed.\n");
	printf("1. Add element (array-based)\n");
	printf("2. Remove element (array-based)\n");
	printf("3. Add element (list-based)\n");
	printf("4. Remove element (list-based)\n");
	printf("5. Analize and print results\n");
	printf("0. Exit\n");

	ArrayStack astack;
	arrstack_create(&astack);
	ListUnit *lstack;
	liststack_create(&lstack);

	int command;
	int error = 0;
	do
	{
		fflush(stdin);
		printf("\nInput the command: ");
		if (scanf("%d", &command) != 1)
		{			
			error = ERROR_INCORRECT_INPUT_SYMBOLS;
			command = -1;
		}
		else if (command == 0)
		{
			printf("Finishing\n");
			error = 0;
		}
		else if (command == 1)
		{
			int elem;
			printf("Input element: ");
			if (scanf("%d", &elem) != 1)
			{
				error = ERROR_INCORRECT_INPUT_SYMBOLS;
			}
			else
			{
				error = arrstack_add(&astack, elem);
			}
		}
		else if (command == 2)
		{
			int elem;			
			error = arrstack_remove(&astack, &elem);
			if (error == 0)
				printf("\nRemoved from array-based stack element value is: %d\n", elem);
		}
		else if (command == 3)
		{
			int elem;
			printf("Input element: ");
			if (scanf("%d", &elem) != 1)
			{
				error = ERROR_INCORRECT_INPUT_SYMBOLS;
			}
			else
			{
				error = liststack_add(&lstack, elem);
			}
		}
		else if (command == 4)
		{
			int elem;
			error = liststack_remove(&lstack, &elem);
			if (error == 0)
				printf("\nRemoved from list-based stack element value is: %d\n", elem);
		}
		else if (command == 5)
		{
			analize();
		}
		else
			error = ERROR_UNRECOGNIZED_COMMAND;

		// Handling error
		switch (error)
		{
		case ERROR_UNRECOGNIZED_COMMAND:
			printf("Unrecognized command!\n");
			break;
		case ERROR_INCORRECT_INPUT_SYMBOLS:
			printf("Incorrect input. Some illegal symbols was found.\n");
			break;
		case ERROR_ALLOCATION_ERROR:
			printf("Unable to allocate memory!\n");
			break;
		case ERROR_STACK_ARR_EMPTY:
			printf("Array-based stack is empty.\n");
			break;
		case ERROR_STACK_LIST_EMPTY:
			printf("List-based stack is empty.\n");
			break;
		case ERROR_STACK_ARR_OVERFLOW:
			printf("Array-based stack is full.\n");
			break;
		default:
			printf("Success!\n");
		}

	} while (command != 0);

	return 0;
}

void analize()
{
	ArrayStack astack;
	arrstack_create(&astack);
	ListUnit *lstack;
	liststack_create(&lstack);

	srand(rand());

	// Filling with random data

	unsigned __int64 adding_time_arr = tick();
	for (int i = 0; i < STACK_ARR_MAXSIZE; i++)
	{
		arrstack_add(&astack, rand() % 100);		
	}
	adding_time_arr = tick() - adding_time_arr;

	unsigned __int64 adding_time_list = tick();
	for (int i = 0; i < STACK_ARR_MAXSIZE; i++)
	{
		liststack_add(&lstack, rand() % 100);
	}
	adding_time_list = tick() - adding_time_list;

	// Removing

	unsigned __int64 removing_time_arr = tick();
	for (int i = 0; i < STACK_ARR_MAXSIZE; i++)
	{
		int elem;
		arrstack_remove(&astack, &elem);
	}
	removing_time_arr = tick() - removing_time_arr;

	unsigned __int64 removing_time_list = tick();
	for (int i = 0; i < STACK_ARR_MAXSIZE; i++)
	{
		int elem;
		liststack_remove(&lstack, &elem);
	}
	removing_time_list = tick() - removing_time_list;

	
	// Counting memory
	int arr_mem = sizeof(ArrayStack);
	int list_mem = sizeof(ListUnit)* STACK_ARR_MAXSIZE;

	// Printing results

	printf("Array based stack: \n");
	printf("	Adding time: %llu\n", adding_time_arr);
	printf("	Removing time: %llu\n", removing_time_arr);
	printf("	Memory: %d\n", arr_mem);

	printf("\nList based stack: \n");
	printf("	Adding time: %llu\n", adding_time_list);
	printf("	Removing time: %llu\n", removing_time_list);
	printf("	Memory: %d\n", list_mem);

	// Percentage
	printf("Adding time, array-based time is smaller than list-based in %2.2f times\n", (float)adding_time_list / adding_time_arr);
	printf("Removing time, array-based time is smaller than list-based in %2.2f times\n", (float)removing_time_list / removing_time_arr);
	printf("Array-based memeory is smaller than list-based memeory in %2.2f times\n", (float)list_mem / arr_mem);
}