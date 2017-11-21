#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include "queue.h"

#define TICK_TIME 0.1f
#define T1_ADD_MIN 1
#define T1_ADD_MAX 5
#define T2_ADD_MIN 0
#define T2_ADD_MAX 3
#define T1_SERVING_MIN 0
#define T1_SERVING_MAX 4
#define T2_SERVING_MIN 0
#define T2_SERVING_MAX 1

#define RAND(min, max)  (rand() / RAND_MAX) * (max - min) + min

void ProcessList();

int lqlen(lqueue *lq)
{
	int len = 0;
	lunit *u = lq->pout;
	while (u != NULL)
	{
		len++;
	}
	return len;
}

int main()
{
	srand(time(NULL));
	ProcessList();

	_getch();
}

void ProcessList()
{
	lqueue queue1;
	lqueue queue2;
	lqcreate(&queue1);
	lqcreate(&queue2);

	float total_time = 0;
	float process_time = 0;
	float standing_time = 0;
	float add_time1 = 0;
	float add_time2 = 0;
	int out1 = 0;
	int out2 = 0;
	int in1 = 0;
	int in2 = 0;
	int state = 0;	
	int total_length1 = 0;
	int total_length2 = 0;
	int cur_info = 0;

	while (out1 < 1000)
	{
		total_time += TICK_TIME;

		// Info
		if (out1 % 100 == 0 && out1 != 0)
		{
			printf("");
		}

		// Process
		if (state != 0)
		{
			if (process_time > 0)
				process_time -= TICK_TIME;
			else
			{
				process_time = 0;
				if (state == 1)
					out1++;
				else
					out2++;
				state = 0;
			}
		}
		else
			standing_time += TICK_TIME;

		// Get
		else if (state == 0)
		{
			int type1 = lqremove(&queue1, NULL);
			int type2 = 0;
			if (type1)
			{
				type2 = lqremove(&queue2, NULL);
				if (!type2)
				{
					state = 2;
					process_time = RAND(T2_SERVING_MIN, T2_SERVING_MAX);
				}
			}
			else
			{
				state = 1;
				process_time = RAND(T1_SERVING_MIN, T1_SERVING_MAX);
			}
		}

		else
		{
			int type1 = lqremove(&queue1, NULL);
			if (!type1)
			{
				state = 1;
				process_time = RAND(T1_SERVING_MIN, T1_SERVING_MAX);
				lqadd(&queue2, 0);
			}
		}

		// Add
		if (add_time1 > 0)
			add_time1 -= TICK_TIME;
		else
		{
			lqadd(&queue1, 1); // TODO error check
			in1++;
			add_time1 = RAND(T1_ADD_MIN, T1_ADD_MAX);
		}

		if (add_time2 > 0)
			add_time2 -= TICK_TIME;
		else
		{
			lqadd(&queue2, 2); // TODO error check
			in2++;
			add_time2 = RAND(T2_ADD_MIN, T2_ADD_MAX);
		}
	}

	printf("Success!\nTotal time: %3.2f\nStanding time: %3.2f\nIn1: %d, Out1: %d\nIn2: %d, Out2: %d\n", total_time, standing_time, in1, out1, in2, out2);
}
