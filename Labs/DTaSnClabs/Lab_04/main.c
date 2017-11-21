/* Монахов Д.И. ИУ7-34
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#include "queue.h"

#define ERROR_UNRECOGNIZED_COMMAND -1111

// Main prefs
#define ARRAY_SIZE 5
#define REPEATS_COUNT 100
#define ARRAY_SIZE_ANALIZE 1000

// Simulation prefs
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


#pragma intrinsic(__rdtsc)
unsigned __int64 tick()
{
	return __rdtsc();
}

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
		if (state == 0)
			standing_time += TICK_TIME;
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
	printf("Ignored apps type 2: %d\n", in2 - out2);
	printf("Average time of type 1: %3.2f\n", (1 + (float)total_length1 / cur_info / 2) * (float)(T1_SERVING_MAX - T1_ADD_MIN) / 2);
	printf("Average time of type 2: %3.2f\n", (1 + (float)total_length2 / cur_info / 2) * (float)(T2_SERVING_MAX - T2_ADD_MIN) / 2);
}

int main()
{
	int command = -1;

	printf("1. Add\n");
	printf("2. Remove\n");
	printf("3. Print\n");
	printf("4. Print pure\n");
	printf("5. Add to list\n");
	printf("6. Remove from list\n");
	printf("7. Print list\n");
	printf("8. Start Processing Device simulation\n");
	printf("9. Analize times and memory\n");

	aqueue q;
	aqcreate(&q, ARRAY_SIZE);
	lqueue lq;
	lqcreate(&lq);

	int cnt = 0;
	while (command != 0)
	{
		cnt++;
		printf("Input command: ");
		scanf("%d", &command);

		int err = 0;

		if (command == 1)
		{
			float num;
			printf("Input an element to add: ");
			scanf("%f", &num);
			printf("Adding %3.2f\n", num);
			err = aqadd(&q, num);
		}
		else if (command == 2)
		{
			float res;
			err = aqremove(&q, &res);
			if (err == 0)
				printf("Removed element: %2.2f\n", res);
		}
		else if (command == 3)
		{
			while (err == 0)
			{
				float res;
				err = aqremove(&q, &res);
				if(!err) printf("%2.2f ", res);
			}
			printf("\n");
		}
		else if (command == 4)
		{
			printf("Pout pos: %d, Pin pos: %d\n", q.pout - q.data, q.pin - q.data);
			for (int i = 0; i < &q.data[q.size] - q.data; i++)
			{
				printf("%2.2f ", q.data[i]);
			}
			printf("\n");
		}
		else if (command == 5)
		{
			float num;
			printf("Input an element to add: ");
			scanf("%f", &num);
			printf("Adding %3.2f\n", num);
			err = lqadd(&lq, num);
		}
		else if (command == 6)
		{
			float res;
			err = lqremove(&lq, &res);
			if (!err)
				printf("Removing %2.2f\n", res);
		}
		else if (command == 7)
		{
			lunit *u = lq.pout;
			while (u != NULL)
			{
				printf("%2.2f ", u->value);
				u = u->next;
			}
			printf("\n");
		}
		else if (command == 8)
		{
			ProcessList();
			err = 0;
		}
		else if (command == 9)
		{
			// Checking array
			unsigned long long array_add = 0;
			unsigned long long  array_remove = 0;
			unsigned long long  array_init = 0;
			struct aqueue arrq;
			array_init = tick();
			aqcreate(&arrq, ARRAY_SIZE_ANALIZE);
			array_init = tick() - array_init;
			for (int i = 0; i < REPEATS_COUNT; i++)
			{
				unsigned long long add = tick();
				for (int k = 0; k < ARRAY_SIZE_ANALIZE; k++)
				{
					aqadd(&arrq, k);
				}		
				add = tick() - add;
				array_add += add;
				
				unsigned long long rem = tick();
				for (int k = 0; k < ARRAY_SIZE_ANALIZE; k++)
				{
					aqremove(&arrq, NULL);
				}
				rem = tick() - rem;
				array_remove += rem;
			}
			array_add /= REPEATS_COUNT;
			array_remove /= REPEATS_COUNT;

			// Checking list
			unsigned long long  list_add = 0;
			unsigned long long  list_remove = 0;
			unsigned long long  list_init = 0;
			struct lqueue lisq;
			list_init = tick();
			lqcreate(&lisq);
			list_init = tick() - list_init;
			for (int i = 0; i < REPEATS_COUNT; i++)
			{
				unsigned long long add = tick();
				for (int k = 0; k < ARRAY_SIZE_ANALIZE; k++)
				{
					lqadd(&lisq, k);
				}
				add = tick() - add;
				list_add += add;

				unsigned long long rem = tick();
				for (int k = 0; k < ARRAY_SIZE_ANALIZE; k++)
				{
					lqremove(&lisq, NULL);
				}
				rem = tick() - rem;
				list_remove += rem;
			}
			array_add /= REPEATS_COUNT;
			array_remove /= REPEATS_COUNT;
			list_add /= REPEATS_COUNT;
			list_remove /= REPEATS_COUNT;

			printf("Array initialization time: %llu\n", array_init);
			printf("Array adding time: %llu\n", array_add);
			printf("Array removing time: %llu\n", array_remove);
			printf("List initialization time: %llu\n", list_init);
			printf("List adding time: %llu\n", list_add);
			printf("List removing time: %llu\n", list_remove);
			
			printf("Ratios (array to list): \n");
			printf("  Initializing: %10.10f\n", (double)array_init / (double)list_init);
			printf("        Adding: %10.10f\n", (double)array_add / (double)list_add);
			printf("      Removing: %10.10f\n", (double)array_remove / (double)list_remove);
		}
		else
			err = ERROR_UNRECOGNIZED_COMMAND;

		switch (err)
		{
		case ERROR_AQ_OVERFLOW:
			printf("Array-queue is full\n");
			break;
		case ERROR_AQ_EMPTY:
			printf("Array-queue is empty\n");
			break;
		case ERROR_UNRECOGNIZED_COMMAND:
			printf("Unknown command\n");
			break;
		case ERROR_ALLOCATION:
			printf("Allocation error\n");
			break;
		case ERROR_LQ_EMPTY:
			printf("List-queue is empty\n");
			break;
		}
	}
}
