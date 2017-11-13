#include "servdev.h"
#include "queue.h"
#include <conio.h>
#include <stdio.h>

int main(void)
{
	//printf("With array-based queue: \n");
	//StartProcessing(ArrayBased);

	printf("\nWith list-based queue: \n");
	StartProcessing(ListBased);

	printf("\nSuccess!\n");
	_getch();
}
