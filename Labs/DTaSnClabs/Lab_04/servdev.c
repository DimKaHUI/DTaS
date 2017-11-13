#include "servdev.h"
#include <stdlib.h>
#include "time.h"
#include <stdio.h>
#include <conio.h>

#define TICK_TIME 0.01f
#define T1_ADD_MIN 1
#define T1_ADD_MAX 5
#define T2_ADD_MIN 0
#define T2_ADD_MAX 3
#define T1_SERVING_MIN 0
#define T1_SERVING_MAX 4
#define T2_SERVING_MIN 0
#define T2_SERVING_MAX 1

#define RAND(min, max)  (rand() / RAND_MAX) * (max - min) + min

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


void StartProcessing(QueueType type)
{
	//astr aques;
	//lstr lques;
	aqueue faq;
	aqueue saq;
	lqueue flq;
	lqueue slq;
	aqcreate(&faq, APP_COUNT);
	aqcreate(&saq, APP_COUNT);
	lqcreate(&flq);
	lqcreate(&slq);

	srand(time(NULL));

	int t1_count_out = 0;
	int t2_count_out = 0;
	int t1_count_in = 0;
	int t2_count_in = 0;
	int t1_summ_len = 0;
	int t2_summ_len = 0;
	int count_of_prints = 1;

	float total_time = 0;
	float proc_time = 0;
	float add_t1_time = 0;
	float add_t2_time = 0;

	int state = 0;

	if (type == ArrayBased)
	{
		while (t1_count_out < APP_COUNT)
		{			
			//printf("Sate: %d, CurTime: %2.2f, t1_out: %d, t2_out: %d\n", state, proc_time, t1_count_out, t2_count_out);

			// Printing info
			if (t1_count_out % 100 == 0 && t1_count_out != 0 && count_of_prints == t1_count_out / 100 - 1)
			{
				printf("\nReport #%d\n", count_of_prints);
				if (type == ArrayBased)
				{
					printf("First type queue length: %d\n", faq.count);
					printf("Second type queue length: %d\n", saq.count);
					t1_summ_len += faq.count;
					t2_summ_len += saq.count;
					printf("First type queue avarage length: %d\n", t1_summ_len / count_of_prints);
					printf("Second type queue avarage length: %d\n", t2_summ_len / count_of_prints);
				}
				count_of_prints += 1;
			}
			else
			{
			}


			// Processing current app
			total_time += TICK_TIME;
			if (proc_time > 0)
			{				
				proc_time -= TICK_TIME;
			}
			else
			{
				proc_time = 0;
				if (state == 1)
					t1_count_out++;
				if (state == 2)
					t2_count_out++;
				state = 0;
			}


			// Getting new app from queue
			if (proc_time <= 0 && state == 0)
			{
				float value = 0;
				aqremove(&faq, &value);
				if (value != 0)
				{
					state = 1;
					proc_time = RAND(T1_SERVING_MIN, T1_SERVING_MAX);
				}
			}

			if (proc_time <= 0 && state == 2)
			{
				float value = 0;
				aqremove(&faq, &value);
				if (value != 0)
				{
					state = 1;
					proc_time = RAND(T1_SERVING_MIN, T1_SERVING_MAX);
					int err = aqadd(&saq, 1.0f);
					//if (!err)
						//printf("Err = %d\n", err);
				}
			}

			if (proc_time <= 0 && state == 0)
			{
				float value = 0;
				aqremove(&saq, &value);
				//printf("second queue len after removing: %d\n", saq.count);
				if (value != 0)
				{
					state = 2;
					proc_time = RAND(T2_SERVING_MIN, T2_SERVING_MAX);
				}
			}

			

			// Decreasing time of adding
			if (add_t1_time > 0)
				add_t1_time -= TICK_TIME;
			else
				add_t1_time = 0;

			if (add_t2_time > 0)
				add_t2_time -= TICK_TIME;
			else
				add_t2_time = 0;

			// Adding new apps to queue t1
			if (add_t1_time <= 0)
			{
				add_t1_time = RAND(T1_ADD_MIN, T1_ADD_MAX);
				aqadd(&faq, 1.0f);
			}

			// Adding new apps to queue t2
			if (add_t2_time <= 0)
			{
				add_t2_time = RAND(T2_ADD_MIN, T2_ADD_MAX);
				aqadd(&saq, 1.0f);
				//printf("second queue len after ADDING: %d\n", saq.count);
			}
		}
	}

	else if (type == ListBased)
	{
		while (t1_count_out < APP_COUNT)
		{
			//printf("Sate: %d, CurTime: %2.2f, t1_out: %d, t2_out: %d\n", state, proc_time, t1_count_out, t2_count_out);

			// Printing info
			if (t1_count_out % 100 == 0 && t1_count_out != 0 && count_of_prints == t1_count_out / 100 - 1)
			{
				printf("\nReport #%d\n", count_of_prints);
				if (type == ArrayBased)
				{
					int len1 = lqlen(&flq);
					int len2 = lqlen(&slq);
					printf("First type queue length: %d\n", len1);
					printf("Second type queue length: %d\n", len2);
					t1_summ_len += len1;
					t2_summ_len += len2;
					printf("First type queue avarage length: %d\n", t1_summ_len / count_of_prints);
					printf("Second type queue avarage length: %d\n", t2_summ_len / count_of_prints);
				}
				count_of_prints += 1;
			}
			else
			{
			}


			// Processing current app
			total_time += TICK_TIME;
			if (proc_time > 0)
			{
				proc_time -= TICK_TIME;
			}
			else
			{
				proc_time = 0;
				if (state == 1)
					t1_count_out++;
				if (state == 2)
					t2_count_out++;
				state = 0;
			}


			// Getting new app from queue
			if (proc_time <= 0 && state == 0)
			{
				float value = 0;
				lqremove(&flq, &value);
				if (value != 0)
				{
					state = 1;
					proc_time = RAND(T1_SERVING_MIN, T1_SERVING_MAX);
				}
			}

			if (proc_time <= 0 && state == 2)
			{
				float value = 0;
				lqremove(&flq, &value);
				if (value != 0)
				{
					state = 1;
					proc_time = RAND(T1_SERVING_MIN, T1_SERVING_MAX);
					int err = lqadd(&slq, 1.0f);
					//if (!err)
					//printf("Err = %d\n", err);
				}
			}

			if (proc_time <= 0 && state == 0)
			{
				float value = 0;
				lqremove(&slq, &value);
				//printf("second queue len after removing: %d\n", saq.count);
				if (value != 0)
				{
					state = 2;
					proc_time = RAND(T2_SERVING_MIN, T2_SERVING_MAX);
				}
			}



			// Decreasing time of adding
			if (add_t1_time > 0)
				add_t1_time -= TICK_TIME;
			else
				add_t1_time = 0;

			if (add_t2_time > 0)
				add_t2_time -= TICK_TIME;
			else
				add_t2_time = 0;

			// Adding new apps to queue t1
			if (add_t1_time <= 0)
			{
				add_t1_time = RAND(T1_ADD_MIN, T1_ADD_MAX);
				lqadd(&flq, 1.0f);
			}

			// Adding new apps to queue t2
			if (add_t2_time <= 0)
			{
				add_t2_time = RAND(T2_ADD_MIN, T2_ADD_MAX);
				lqadd(&slq, 1.0f);
				//printf("second queue len after ADDING: %d\n", saq.count);
			}
		}
	}

	else
	{
		printf("Unknown queue type\n");
	}


	printf("Total time: %6.2f\n", total_time);
}