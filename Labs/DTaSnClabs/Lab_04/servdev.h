#pragma once

#include "queue.h"

#define APP_COUNT 1000

typedef enum QueueType
{
	ArrayBased, ListBased
}QueueType;

void StartProcessing(QueueType type);