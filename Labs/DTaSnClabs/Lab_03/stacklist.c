#include <stdio.h>
#include <stdlib.h>
#include "stacklist.h"


int liststack_add(ListUnit** stack, int a)
{
	int size = 0;
	ListUnit *counter = *stack;
	while (counter != NULL)
	{
		size++;
		counter = counter->prev;
	}
	if (size >= STAK_LIST_MAXSIZE)
		return ERROR_STACK_LIST_OVERFLOW;

	//printf("\nSize: %d\n", size);
	if (liststack_is_empty(stack))
	{
		*stack = malloc(sizeof(ListUnit));
		if (*stack == NULL)
		{
			return ERROR_ALLOCATION_ERROR;
		}
		ListUnit unit = { .val = a, .prev = NULL };
		**stack = unit;
		return 0;
	}

	ListUnit *prev = *stack;
	*stack = malloc(sizeof(ListUnit));
	if (*stack == NULL)
	{
		return ERROR_ALLOCATION_ERROR;
	}
	ListUnit unit = { .val = a, .prev = prev };
	**stack = unit;

	return 0;
}

int liststack_remove(ListUnit** stack, int* result)
{
	if (*stack == NULL)
	{
		return ERROR_STACK_LIST_EMPTY;
	}
	ListUnit *prev = (*stack)->prev;
	*result = (*stack)->val;
	free(*stack);
	*stack = prev;
	return 0;
}

int liststack_is_empty(ListUnit** stack)
{
	return *stack == NULL;
}

void liststack_create(ListUnit **stack)
{
	*stack = NULL;
}
