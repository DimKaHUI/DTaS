#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "mysnprintf.h"
#include "string.h"
#include <conio.h>


#define BUFF_LEN 71

void clearbuff(char *buff)
{
	for (int i = 0; i < BUFF_LEN; i++)
		buff[i] = '\0';
}

int main(void)
{
	printf("TEST1. Cutting and extra argument\n");
	char buffer[BUFF_LEN] = "";
	char check_buffer[BUFF_LEN];
	char format_1[] = "Test string number %i is very simple, because %s is similar with %li, right? %s";
	int result_1 = my_snprintf(buffer, BUFF_LEN - 1, format_1, 123, "385", 385L, "SHALL_NOT_BE_PRINTED");
	int check_1 = _snprintf(check_buffer, BUFF_LEN - 1, format_1, 123, "385", 385L, "SHALL_NOT_BE_PRINTED");
	if (result_1 == check_1 && streq(buffer, check_buffer))
		printf("Test completed!\n");
	else
		printf("Test failed\nCorrect len: %d, correct string:\n%s\n", check_1, check_buffer);
	
	printf("\nTEST2. Injection\n");

	clearbuff(buffer);

	char format_2[] = "INJECTION_%i%li%s_INJECTION";
	int result_2 = my_snprintf(buffer, BUFF_LEN - 1, format_2, 0, -123, "III");
	int check_2 = _snprintf(check_buffer, BUFF_LEN - 1, format_2, 0, -123, "III");
	if (result_2 == check_2 && streq(buffer, check_buffer))
		printf("Test completed!\n");
	else
		printf("Test failed\nCorrect len: %d, correct string:\n%s\n", check_2, check_buffer);
	

	clearbuff(buffer);
	clearbuff(check_buffer);


	printf("\nTEST3. n == 0\n");
	char format_3[] = "SomeText %li";
	int result_3 = my_snprintf(buffer, 0, format_3, 0l);
	int check_3 = _snprintf(check_buffer, 0, format_3, 0l);
	if (result_3 == check_3 && streq(buffer, check_buffer))
		printf("Test completed!\n");
	else
		printf("Test failed\nCorrect len: %d, correct string:\n%s\nYour string:\n%s\n", check_3, check_buffer, buffer);

	printf("\nTEST4. n == 1\n");
	char format_4[] = "SomeText %li";
	int result_4 = my_snprintf(buffer, 0, format_4, 0l);
	int check_4 = _snprintf(check_buffer, 0, format_4, 0l);
	if (result_4 == check_4 && streq(buffer, check_buffer))
		printf("Test completed!\n");
	else
		printf("Test failed\nCorrect len: %d, correct string:\n%s\nYour string:\n%s\n", check_4, check_buffer, buffer);

	printf("\nTEST5. No formats, but some additional args\n");
	char format_5[] = "SomeText";
	int result_5 = my_snprintf(buffer, 0, format_5, 0l);
	int check_5 = _snprintf(check_buffer, 0, format_5, 0l);
	if (result_5 == check_5 && streq(buffer, check_buffer))
		printf("Test completed!\n");
	else
		printf("Test failed\nCorrect len: %d, correct string:\n%s\nYour string:\n%s\n", check_5, check_buffer, buffer);

	printf("\nTEST6. Empty string\n");
	char format_6[] = "";
	int result_6 = my_snprintf(buffer, 6, format_6, 0l);
	int check_6 = _snprintf(check_buffer, 6, format_6, 0l);
	if (result_6 == check_6 && streq(buffer, check_buffer))
		printf("Test completed!\n");
	else
		printf("Test failed\nCorrect len: %d, correct string:\n|%s|\nYour string (%d):\n|%s|\n", check_6, check_buffer, result_6, buffer);


	clearbuff(buffer);
	clearbuff(check_buffer);


	printf("\nTEST7. Empty string and n == 0\n");
	char format_7[] = "";
	int result_7 = my_snprintf(buffer, 0, format_7);
	int check_7 = _snprintf(check_buffer, 0, format_7);
	if (result_7 == check_7 && streq(buffer, check_buffer))
		printf("Test completed!\n");
	else
		printf("Test failed\nCorrect len: %d, correct string:\n%s\nYour string (%d):\n%s\n", check_7, check_buffer, result_7, buffer);

	printf("\nTEST8. n == 1, including specificator\n");
	char format_8[] = "%iSomeText";
	int result_8 = my_snprintf(buffer, 1, format_8, 410);
	int check_8 = _snprintf(check_buffer, 1, format_8, 410);
	if (result_8 == check_8 && streq(buffer, check_buffer))
		printf("Test completed!\n");
	else
		printf("Test failed\nCorrect len: %d, correct string:\n%s\nYour string (%d):\n%s\n", check_8, check_buffer, result_8, buffer);

	_getch();
}
