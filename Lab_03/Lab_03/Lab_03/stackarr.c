#include "stackarr.h"

int arrstack_remove(ArrayStack* stack, int *result)
{
	if (stack->ps <= &(stack->arr[0]) - 1)
		return ERROR_STACK_ARR_EMPTY;

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

ArrayStack arrstack_create()
{
	ArrayStack stack;
	stack.ps = &stack.arr[0] - 1;
	return stack;
}

int arrstack_add(ArrayStack *stack, int a)
{
	if (stack->ps == &stack->arr[STACK_ARR_MAXSIZE - 1])
		return ERROR_STACK_ARR_OVERFLOW;

	stack->ps++;
	*stack->ps = a;
	return 0;
}