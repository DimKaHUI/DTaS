#pragma once
#include <stdlib.h>

// List-based stack
typedef struct ListStack
{
	int *ps;
	int length;
} ListStack;

int liststack_add(ListStack *stack, int a);
int liststack_remove(ListStack *stack, int *result);
int liststack_is_empty(ListStack *stack);
ListStack liststack_create();