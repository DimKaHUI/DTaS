#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include <stdio.h>

size_t lunit_size;

int aqadd(aqueue* queue, float x)
{
	if (queue->count > queue->size)
		return ERROR_AQ_OVERFLOW;

	queue->count++;
	*queue->pin = x;
	queue->pin++;

	if (queue->pin > queue->data + queue->size - 1)
	{
		queue->pin = queue->data;
	}
	return 0;
}

int aqremove(aqueue* queue, float *res)
{
	if (queue->count <= 0)
	{
		return ERROR_AQ_EMPTY;
	}

	queue->count--;
	if (res != NULL)
		*res = *queue->pout;
	*queue->pout = 0;
	queue->pout++;
	if (queue->pout > queue->data + queue->size - 1)
	{
		queue->pout = queue->data;
	}

	return 0;
}

int aqcreate(aqueue* queue, int size)
{
	assert(size > 0);
	queue->data = malloc(sizeof(float)* size);
	if (queue->data == NULL)
		return ERROR_ALLOCATION;
	queue->pin = queue->pout = queue->data;
	queue->size = size;
	queue->count = 0;
	return 0;
}

int lqadd(lqueue* queue, float x)
{	
	if (queue->pin == NULL)
	{		
		queue->pin = malloc(lunit_size);
		queue->pout = queue->pin;
	}
	else
	{
		queue->pin->next = malloc(lunit_size);
		queue->pin = queue->pin->next;
	}

	if (queue->pin == NULL)
		return ERROR_ALLOCATION;

	queue->pin->next = NULL;
	queue->pin->value = x;

	return 0;
}

int lqremove(lqueue* queue, float *res)
{
	if (queue->pout == NULL)
	{
		return ERROR_LQ_EMPTY;
	}

	//if (queue->pout->value != NULL)
	if (res != NULL)
	{

		lunit *u = queue->pout;
		*res = u->value;
	}

	lunit *npout = queue->pout->next;
	free(queue->pout);
	queue->pout = npout;
	if (npout == NULL)
		queue->pin = NULL;
	return 0;
}

void lqcreate(lqueue* queue)
{
	queue->pin = NULL;
	queue->pout = NULL;
	lunit_size = sizeof(lunit);
}


