#pragma once

#include "queue.h"

#define APP_COUNT 10

typedef struct astr
{
	aqueue firstq;
	aqueue secondq;
} astr;

typedef struct lstr
{
	lqueue firstq;
	lqueue secondq;
} lstr;

typedef enum QueueType
{
	ArrayBased, ListBased
}QueueType;

typedef struct ServingDevice
{
	float total_time;
	union Queues
	{
		astr aques;
		lstr lques;		
	} Queues;
} ServingDevice;

void StartProcessing(QueueType type);