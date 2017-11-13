#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include <stdio.h>

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
		return ERROR_AQ_EMPTY;

	queue->count--;
	*res = *queue->pout;
	*queue->pout = 0;
	queue->pout++;
	\
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
	//printf("Size: %d\n", sizeof(lunit));
	lunit *unit = malloc(8);
	
	if (unit == NULL)
	{
		return ERROR_ALLOCATION;
	}
	unit->next = NULL;
	unit->value = x;
	if (queue->pin != NULL)
	{
		queue->pin->next = unit;
		queue->pin = unit;		
	}
	else
	{
		queue->pin = unit;
		queue->pout = unit;
	}
	
	return 0;
}

int lqremove(lqueue* queue, float *result)
{
	if (queue->pout == NULL)
		return ERROR_LQ_EMPTY;
	*result = queue->pout->value;
	lunit *next = queue->pout->next;
	//if (queue->pout != NULL)
	free(queue->pout);
	queue->pout = next;
	return 0;
}

void lqcreate(lqueue* queue)
{
	queue->pin = NULL;
	queue->pout = NULL;
}
