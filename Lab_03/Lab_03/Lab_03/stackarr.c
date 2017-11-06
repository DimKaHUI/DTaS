#include <stdio.h>
#include "stackarr.h"

int arrstack_remove(ArrayStack* stack, int *result)
{
	if (stack->ps <= stack->arr - 1)
	{
		return ERROR_STACK_ARR_EMPTY;
	}

	*result = *stack->ps;
	stack->ps--;
	return 0;
}

int arrstack_is_empty(ArrayStack* stack)
{
	if (stack->ps <= &(stack->arr[0]) - 1)
		return 1;
	return 0;
}

void arrstack_create(ArrayStack *stack)
{
	stack->ps = stack->arr - 1;
}

int arrstack_add(ArrayStack *argstack, int a)
{
	if (argstack->ps >= &argstack->arr[STACK_ARR_MAXSIZE - 1])
	{
		argstack->ps = &argstack->arr[STACK_ARR_MAXSIZE - 1];
		return ERROR_STACK_ARR_OVERFLOW;
	}

	argstack->ps++;
	*(argstack->ps) = a;
	return 0;
}