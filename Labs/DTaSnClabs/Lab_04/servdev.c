#include "servdev.h"
#include <stdlib.h>
#include "time.h"
#include <stdio.h>

#define TICK_TIME 0.01f
#define T1_ADD_MIN 1
#define T1_ADD_MAX 5
#define T2_ADD_MIN 0
#define T2_ADD_MAX 3
#define T1_SERVING_MIN 0
#define T1_SERVING_MAX 4
#define T2_SERVING_MIN 0
#define T2_SERVING_MAX 1


void StartProcessing(QueueType type)
{
	/*union Queues
	{
		astr aques;
		lstr lques;
	} Queues;*/
	//astr aques;
	struct aqueue faq;
	struct aqueue saq;
	struct lqueue flq;
	struct lqueue slq;
	//lstr lques;

	srand(time(NULL));
	int t1_count_out = 0;
	int t2_count_out = 0;
	int t1_count_in = 0;
	int t2_count_in = 0;

	if (type == ArrayBased)
	{
		//printf("Array based init\n");
		aqcreate(&aques.firstq, APP_COUNT + 1);
		aqcreate(&aques.secondq, APP_COUNT + 1);
	}
	else
	{
		lqcreate(&lques.firstq);
		lqcreate(&lques.secondq);
		//printf("Init list\n");
	}

	float total_time = 0;
	float current_time = 0;
	float adding_time_t1 = 0;
	float adding_time_t2 = 0;
	int current_application = 0;
	
	while (t1_count_out < APP_COUNT - 1)
	{
		//printf("T1_out: %d, T1_in: %d, State: %d, CurTime %4.2f\n", t1_count_out, t1_count_in, current_application, current_time);
		// Operating with application
		if (current_application != 0)
		{
			total_time += TICK_TIME;
			current_time -= TICK_TIME;
			if (current_time <= 0)
			{
				current_time = 0;
				if (current_application == 1)
					t1_count_out++;
				if (current_application == 2)
					t2_count_out++;
				current_application = 0;				
			}
		}

		if (current_application == 0 || current_application == 2)
		{

			// Getting new application
			float t1_application = 0, t2_application = 0;
			if (type == ArrayBased)
			{
				int err1 = aqremove(&aques.firstq, &t1_application);
				int err2 = aqremove(&aques.secondq, &t2_application);
				//printf("err1: %d, err2: %d\n", err1, err2);
				if (t1_application != 0)
				{
					aqadd(&aques.secondq, t2_application);
					current_application = 1;
					current_time = (T1_SERVING_MIN * 100 + rand() % T1_SERVING_MAX * 100) / 100.0f;
				}
				else if (t2_application != 0 && current_application == 0)
				{
					current_application = 2;
					current_time = (T2_SERVING_MIN * 100 + rand() % T2_SERVING_MAX * 100) / 100.0f;
				}
				else
					current_application = 0;
			}
			else
			{
				int err1 = lqremove(&lques.firstq, &t1_application);
				int err2 = lqremove(&lques.secondq, &t2_application);
				
				if (t1_application != 0)
				{
					lqadd(&lques.secondq, t2_application);
					current_application = 1;
					current_time = (T1_SERVING_MIN * 100 + rand() % T1_SERVING_MAX * 100) / 100.0f;
				}
				else if (t2_application != 0 && current_application == 0)
				{
					current_application = 2;
					current_time = (T2_SERVING_MIN * 100 + rand() % T2_SERVING_MAX * 100) / 100.0f;
				}
				else
					current_application = 0;
			}
		}

		// Adding new application to T1 queue
		adding_time_t1 -= TICK_TIME;
		if (adding_time_t1 <= 0)
		{
			if (type == ArrayBased)
			{
				if (aqadd(&aques.firstq, 1) == 0)
				{
					t1_count_in++;
					adding_time_t1 = (T1_ADD_MIN * 100 + rand() % T1_ADD_MAX * 100) / 100.0f;
				}
			}
			else
			{
				//printf("Adding to list t1\n");
				if (lqadd(&lques.firstq, 2) == 0)
				{
					t1_count_in++;
					adding_time_t1 = (T1_ADD_MIN * 100 + rand() % T1_ADD_MAX * 100) / 100.0f;
				}
				else
				{
					printf("Adding error\n");
				}
			}

		}

		// Adding new application to T2 queue
		adding_time_t2 -= TICK_TIME;
		if (adding_time_t2 <= 0)
		{
			if (type == ArrayBased)
			{
				aqadd(&aques.secondq, 2);
				adding_time_t2 = (T2_ADD_MIN * 100 + rand() % T2_ADD_MAX * 100) / 100.0f;
				t2_count_in++;
			}
			else
			{
				int err = lqadd(&lques.secondq, 2);
				if (err == 0)
				{
					adding_time_t2 = (T2_ADD_MIN * 100 + rand() % T2_ADD_MAX * 100) / 100.0f;
					t2_count_in++;
				}
				else
				{
					printf("Adding error T2: %d\n", err);
				}
			}
		}
		
	}

	printf("Total time: %6.2f\n", total_time);
}