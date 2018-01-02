#pragma once

#define ERROR_DINARR_ALLOCATION -101
#define ERROR_DINARR_EMPTY -102

typedef struct DinArrStack
{
	float *arr;
	float *ps;
} DinArrStack;

int dinarr_add(DinArrStack *stack, float a);
int dinarr_remove(DinArrStack *stack, float *result);
int dinarr_is_empty(DinArrStack *stack);
void dinarr_create(DinArrStack *stack);