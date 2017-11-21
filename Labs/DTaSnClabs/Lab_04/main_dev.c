#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include "queue.h"

#define TICK_TIME 0.1f
#define T1_ADD_MIN 1.0f
#define T1_ADD_MAX 5.0f
#define T2_ADD_MIN 0.0f
#define T2_ADD_MAX 3.0f
#define T1_SERVING_MIN 0.0f
#define T1_SERVING_MAX 4.0f
#define T2_SERVING_MIN 0.0f
#define T2_SERVING_MAX 1.0f

#define RAND(t1, t2)  ((float)rand() / RAND_MAX) * (t2 - t1) + t1

void ProcessList();

int lqlen(lqueue *lq)
{
	int len = 0;
	lunit *u = lq->pout;
	while (u != NULL)
	{
		u = u->next;
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
		//printf("Total time: %3.2f\n", total_time);

		// Info
		if (out1 % 100 == 0 && out1 != 0 && out1 / 100 == cur_info + 1)
		{
			cur_info++;
			int len1 = lqlen(&queue1);
			int len2 = lqlen(&queue2);
			total_length1 += len1;
			total_length2 += len2;
			printf("==================================\n");
			printf("Queue 1 length: %d\n", len1);
			printf("Queue 2 length: %d\n", len2);
			printf("Queue 1 average length: %3.2f\n", (float)total_length1 / cur_info);
			printf("Queue 2 average length: %3.2f\n", (float)total_length2 / cur_info);
			printf("Type 1 average time: %3.2f\n", -1.0f);
			printf("Type 2 average time: %3.2f\n", -1.0f);
			printf("==================================\n");
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

		// Get
		else if (state == 0)
		{
			standing_time += TICK_TIME;
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
