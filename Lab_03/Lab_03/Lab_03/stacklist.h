#pragma once
#include <stdlib.h>

// List-based stack

// Error codes
#define ERROR_ALLOCATION_ERROR -21
#define ERROR_STACK_LIST_EMPTY -22

typedef struct ListUnit
{
	int val;
	struct ListUnit *prev;
} ListUnit;


int liststack_add(ListUnit **stack, int a);
int liststack_remove(ListUnit **stack, int *result);
int liststack_is_empty(ListUnit **stack);
void liststack_create(ListUnit**);