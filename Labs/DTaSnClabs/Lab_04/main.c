/* Монахов Д.И. ИУ7-34
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "queue.h"

#define ERROR_UNRECOGNIZED_COMMAND -1111

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

	aqueue q;
	aqcreate(&q, 5);
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
			printf("Adding %d\n", cnt);
			err = aqadd(&q, (float)cnt);
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
			printf("Adding %d\n", cnt);
			err = lqadd(&lq, cnt);
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
