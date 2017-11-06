#pragma once

#define ERROR_DINARR_ALLOCATION -101
#define ERROR_DINARR_EMPTY -102

typedef struct DinArrStack
{
	int *arr;
	int *ps;
} DinArrStack;

int dinarr_add(DinArrStack *stack, int a);
int dinarr_remove(DinArrStack *stack, int *result);
int dinarr_is_empty(DinArrStack *stack);
void dinarr_create(DinArrStack *stack);