#include "dinarrstack.h"
#include <stdlib.h>
#include <stdio.h>

#define BLOCK_ELEMENTS 8

int dinarr_add(DinArrStack* stack, int a)
{
	if (dinarr_is_empty(stack))
	{
		stack->arr = malloc(sizeof(int)*BLOCK_ELEMENTS);
		if (stack->arr == NULL)
		{
			return ERROR_DINARR_ALLOCATION;
		}
		stack->arr[0] = a;
		stack->ps = stack->arr;
		//printf("Array created!\n");
		return 0;
	}

	int cur_size = stack->ps - stack->arr;
	if (cur_size % BLOCK_ELEMENTS == 0)
	{
		//printf("New size: %d\n", new_size * sizeof(int));
		stack->arr = realloc(stack->arr, (cur_size + BLOCK_ELEMENTS) * sizeof(int));
		if (stack->arr == NULL)
		{
			return ERROR_DINARR_ALLOCATION;
		}
	}
	else
	{
		// TODO or not TODO
	}
	stack->ps++;
	*stack->ps = a;
	return 0;
}

int dinarr_remove(DinArrStack* stack, int* result)
{
	if (stack->ps < stack->arr)
	{
		return ERROR_DINARR_EMPTY;
	}
	int cur_size = stack->ps - stack->arr;
	if (cur_size % BLOCK_ELEMENTS == 0)
	{
		//printf("Realloc\n");
		stack->arr = realloc(stack->arr, (cur_size - BLOCK_ELEMENTS) * sizeof(int));
		if (stack->arr == NULL)
		{
			return ERROR_DINARR_ALLOCATION;
		}
	}
	else
	{
		//printf("No realloc\n");
	}
	stack->ps--;
	return 0;
}

int dinarr_is_empty(DinArrStack* stack)
{
	if (stack->ps <= &(stack->arr[0]) - 1)
		return 1;
	return 0;
}

void dinarr_create(DinArrStack* stack)
{
	stack->ps = stack->arr - 1;
}
