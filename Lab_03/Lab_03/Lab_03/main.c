/* Монахов Дмитрий. ИУ7-34. Работа 3
 * 
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#include "stackarr.h"
#include "stacklist.h"
#include "dinarrstack.h"

#define LINE_LENGTH 64

// Error codes
#define ERROR_UNRECOGNIZED_COMMAND -1
#define ERROR_INCORRECT_INPUT_SYMBOLS -2
#define ERROR_READING -3
#define ERROR_LINE_EMPTY -4

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
	printf("6. Check if line is a palindrome\n");
	printf("7. View Array-based stack state\n");
	printf("8. View List-based stack state\n");
	printf("9. View removed elements' addresses\n");
	printf("0. Exit\n");

	ArrayStack astack;
	arrstack_create(&astack);
	ListUnit *lstack;
	liststack_create(&lstack);
	ListUnit *freed;
	liststack_create(&freed);

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
				if (error == 0)
				{
					printf("Address of added element: %d\n", lstack);
				}
			}
		}
		else if (command == 4)
		{
			int elem;
			ListUnit *unit = lstack;
			
			error = liststack_remove(&lstack, &elem);
			if (error == 0)
			{
				liststack_add(&freed, (int)unit);
				printf("\nRemoved from list-based stack element value is: %d\n", elem);
			}
		}
		else if (command == 5)
		{
			analize();
		}
		else if (command == 6)
		{
			printf("Input the line: ");
			fflush(stdin);
			char line[LINE_LENGTH];
			if (gets_s(line, LINE_LENGTH) == NULL)
			{
				fflush(stdin);
				return ERROR_READING;
			}

			fflush(stdin);

			ArrayStack stack;
			arrstack_create(&stack);
			int length = 0;
			for (int i = 0; line[i] != '\0'; i++, length++)
			{
				arrstack_add(&stack, (int)line[i]);
			}

			if (length == 0)
			{
				error = ERROR_LINE_EMPTY;
			}
			else
			{


				int is_palindrome = 1;
				for (int i = length - 1; i >= 0; i--)
				{
					int elem;
					arrstack_remove(&stack, &elem);
					if ((char)elem == line[length - i - 1])
						continue;
					is_palindrome = 0;
				}

				if (is_palindrome)
					printf("This line is a palindrome\n");
				else
					printf("This line is not a palindrome\n");
				error = 0;
			}
		}
		else if (command == 7)
		{
			printf("\nSize: %d\n", astack.ps - astack.arr + 1);
			
			for (int* i = astack.ps; i >= astack.arr; i--)
			{
				printf("%d\n", *i);
			}
		}
		else if (command == 8)
		{
			int size = 0;
			ListUnit *unit = lstack;
			if (unit != NULL)
				printf("Last element: %d\n", lstack->val);
			printf("Elements' addresses: \n");
			while (unit != NULL)
			{
				printf("#%3.3d : %d : %d\n", size + 1, unit, unit->val);
				size++;
				unit = unit->prev;				
			}
			
			printf("\nSize: %d\n", size);			
		}
		else if (command == 9)
		{
			int i = 1;
			while (freed != NULL)
			{
				int val;
				liststack_remove(&freed, &val);
				printf("#%3.3d : %d\n", i, val);
				i++;
			}
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
		case ERROR_LINE_EMPTY:
			printf("The line is empty!\n");
			break;
		case ERROR_READING:
			printf("An error occured while reading the line! May be an overflow, maximum length is %d\n", LINE_LENGTH);
			break;
		case ERROR_STACK_LIST_OVERFLOW:
			printf("Size of list-stack reached it's thresold!.\n");
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
	DinArrStack dstack;
	dinarr_create(&dstack);

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

	unsigned __int64 adding_time_din = tick();
	for (int i = 0; i < STACK_ARR_MAXSIZE; i++)
	{
		dinarr_add(&dstack, rand() % 100);
	}
	adding_time_din = tick() - adding_time_din;

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

	unsigned __int64 removing_time_din = tick();
	for (int i = 0; i < STACK_ARR_MAXSIZE; i++)
	{
		int elem;
		dinarr_remove(&dstack, &elem);
	}
	removing_time_din = tick() - removing_time_din;

	
	// Counting memory
	int arr_mem = sizeof(ArrayStack);
	int list_mem = sizeof(ListUnit)* STACK_ARR_MAXSIZE;
	int din_mem = sizeof(int*)* (STACK_ARR_MAXSIZE + 1);

	// Printing results

	printf("Array based stack: \n");
	printf("	Adding time: %llu\n", adding_time_arr);
	printf("	Removing time: %llu\n", removing_time_arr);
	printf("	Memory: %d\n", arr_mem);

	printf("\nList based stack: \n");
	printf("	Adding time: %llu\n", adding_time_list);
	printf("	Removing time: %llu\n", removing_time_list);
	printf("	Memory: %d\n", list_mem);

	printf("\nDinamic-array based stack: \n");
	printf("	Adding time: %llu\n", adding_time_din);
	printf("	Removing time: %llu\n", removing_time_din);
	printf("	Memory: %d\n", din_mem);

	// Percentage
	printf("Adding time, array-based time is SMALLER than list-based in %2.2f times\n", (float)adding_time_list / adding_time_arr);
	printf("Removing time, array-based time is SMALLER than list-based in %2.2f times\n", (float)removing_time_list / removing_time_arr);
	printf("Array-based memory is SMALLER than list-based memory in %2.2f times\n", (float)list_mem / arr_mem);

	printf("\nAdding time, dinamic array-based time is SMALLER than list-based in %2.2f times\n", (float)adding_time_list / adding_time_din);
	printf("Removing time, dinamic array-based time is BIGGER than list-based in %2.2f times\n", 1 / ((float)removing_time_list / removing_time_din));
	printf("Dinamic Array-based memory is SMALLER than list-based memory in %2.2f times\n", ((float)list_mem / din_mem));
}