#pragma once

// Array-based stack
#define STACK_ARR_MAXSIZE 2000

// Error codes
#define ERROR_STACK_ARR_OVERFLOW -11
#define ERROR_STACK_ARR_EMPTY -12

typedef struct ArrayStack
{
	int arr[STACK_ARR_MAXSIZE];
	int *ps;
} ArrayStack;

int arrstack_add(ArrayStack *stack, int a);
int arrstack_remove(ArrayStack *stack, int *result);
int arrstack_is_empty(ArrayStack *stack);
void arrstack_create(ArrayStack *stack);