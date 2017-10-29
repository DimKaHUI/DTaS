/* Монахов Дмитрий. ИУ7-34. Работа 3
 * 
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "stackarr.h"
#include "stacklist.h"

// Error codes
#define ERROR_UNRECOGNIZED_COMMAND -1
#define ERROR_INCORRECT_INPUT_SYMBOLS -2

int main(void)
{
	printf("Stack\nPring number of menu element to proceed.\n");
	printf("1. Add element (array-based)\n");
	printf("2. Remove element (array-based)\n");
	printf("3. Add element (list-based)\n");
	printf("4. Remove element (list-based)\n");
	printf("5. Print results\n");
	printf("0. Exit\n");

	ArrayStack astack;
	arrstack_create(&astack);
	ListStack lstack = liststack_create();

	int command;
	int error = 0;
	do
	{
		printf("ps = %d, arr = %d\n", astack.ps, astack.arr);

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
				printf("Invoking add.\n");
				error = arrstack_add(&astack, elem);
			}
		}
		else if (command == 2)
		{
			int elem;			
			error = arrstack_remove(&astack, &elem);
			if (error == 0)
				printf("Removed from array-based stack element value is: %d\n", elem);
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
			printf("Removed from list-based stack element value is: %d\n", elem);
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