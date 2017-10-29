#pragma once

// Array-based stack
#define STACK_ARR_MAXSIZE 64

typedef struct ArrayStack
{
	int arr[STACK_ARR_MAXSIZE];
	int *ps;
} ArrayStack;

int arrstack_add(ArrayStack *stack, int a);
int arrstack_remove(ArrayStack *stack);
int arrstack_is_empty(ArrayStack *stack);
ArrayStack arrstack_create();