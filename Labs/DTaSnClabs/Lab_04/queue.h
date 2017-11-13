#pragma once

// Queue specifications
#define ERROR_AQ_OVERFLOW -11
#define ERROR_AQ_EMPTY -12
#define ERROR_ALLOCATION -13
#define ERROR_LQ_EMPTY -14

typedef struct aqueue
{
	float *pin;
	float *pout;
	float *data; // Data array
	unsigned short count; // Amount of kept elements
	unsigned short size; // Overall size of array;
} aqueue;

typedef struct lunit
{
	float value;
	struct lunit *next;
} lunit;

typedef struct lqueue
{
	lunit *pin;
	lunit *pout;
} lqueue;

int aqadd(aqueue *queue, float x);
int aqremove(aqueue *queue, float *res);
int aqcreate(aqueue *queue, int size);

int lqadd(lqueue *queue, float x);
int lqremove(lqueue *queue, float *result);
void lqcreate(lqueue *queue);