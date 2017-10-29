#pragma once

// Array-based stack
#define STACK_ARR_MAXSIZE 64

// Error codes
#define ERROR_STACK_ARR_OVERFLOW -0x11F
#define ERROR_STACK_ARR_EMPTY -0x12F

typedef struct ArrayStack
{
	int arr[STACK_ARR_MAXSIZE];
	int *ps;
} ArrayStack;

int arrstack_add(ArrayStack *stack, int a);
int arrstack_remove(ArrayStack *stack, int *result);
int arrstack_is_empty(ArrayStack *stack);
ArrayStack arrstack_create();