/* Монахов Дмитрий. ИУ7-34. Работа 3
 * 
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// Error codes
#define ERROR_UNRECOGNIZED_COMMAND 0xCD
#define ERROR_INCORRECT_INPUT_SYMBOLS 0xAA

int main(void)
{
	printf("Stack\nPring number of menu element to proceed.");
	printf("1. Add element.\n");
	printf("2. Remove element.\n");
	printf("3. Print results.\n");
	printf("0. Exit\n");

	int command;
	int error = 0;
	do
	{
		printf("\nInput the command: ");
		if (scanf("%d", &command) != 1)
		{
			error = ERROR_INCORRECT_INPUT_SYMBOLS;
		}

		if (command == 0)
		{
			printf("Finishing\n");
			error = 0;
		}
		if (command == 1)
		{
			// TODO
		}
		else if (command == 2)
		{
			// TODO
		}
		else if (command == 3)
		{
			// TODO
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
		default:
			printf("Success!\n");
		}

	} while (command != 0);

	return 0;
}