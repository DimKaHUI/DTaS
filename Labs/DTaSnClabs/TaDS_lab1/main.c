#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include "bigreal.h"



int main(void)
{
	setlocale(LC_ALL, "RUS");

	printf("Спецификация ввода вещественного числа:\n");
	printf("1) Число водится без пробелов\n2) Перед мантиссой явно указывается знак\n");
	printf("3) Перед порядком указывается только знак минус (если порядок отрицательный)\n");
	printf("4) Допустима запись E и в виде строчной и в виде прописной буквы (латиницей)\n");
	printf("5) Длинна манитиссы не должна превышать %d символов (не считая знака)\n", MANTISSA_MAX_SIZE);
	printf("6) Длина порядка не должна превышать %d символов (не считая знака)\n", ORDER_MAX_SIZE);

	bigreal_t dividend;
	bigint_t divisor;
	bigreal_t division;
	printf("Input dividend: \n");
	int input_error = read_real_from_line(&dividend);
	switch (input_error)
	{
	case ERROR_ILLEGAL_FORMAT:
		printf("Некорректный формат ввода вещественного числа.\n");
		break;
	case ERROR_BIGREAL_IO:
		printf("Некорректный ввод: недопустимый символ.\n");
		break;
	case ERROR_DOT_AFTER_E:
		printf("Некорректный ввод: точка в записи порядка.\n");
		break;
	case ERROR_TOO_MANY_DOTS:
		printf("Некорректный ввод: несколько точек\n");
		break;
	case ERROR_TOO_MANY_E:
		printf("Некорректный ввод: несколько E.\n");
		break;		
	case ERROR_NO_SIGN:
		printf("Необходимо явно указывать знак мантиссы.\n");
		break;
	case ERROR_TOO_MANY_SIGNS:
		printf("Слишком много знаков (+/-)\n");
		break;
	case ERROR_TOO_LARGE_MANTISSA:
		printf("Слишком длинная мантисса\n");
		break;
	case ERROR_TOO_LARGE_ORDER:
		printf("Слишком длинная мантисса\n");
		break;
	case ERROR_SIGN_INSIDE_NUMER:
		printf("Знак записан внутри числа.\n");
	}
	//print_real(dividend);
	if (input_error != 0)
	{
		_getch();
		return -1;
	}

	printf("Нормализация: \n");
	int normalization_error = normalize(&dividend);
	if (normalization_error != 0)
		printf("Невозможно нормализовать введенное число.\n");
	print_real(dividend);
	printf("\n");
	
	// Reading divisor
	printf("Введите делитель (большое целое): ");
	input_error = read_int_from_line(&divisor);
	switch (input_error)
	{
	case ERROR_BIGINT_IO:
		printf("Некорректный ввод: недопустимый символ.\n");
		break;
	case ERROR_NO_SIGN:
		printf("Необходимо явно указывать знак.\n");
		break;
	case ERROR_TOO_BIG_INT:
		printf("Длина числа не должна превышать %d", BIGINT_SIZE);
	}
	if (input_error != 0)
	{
		_getch();
		return -1;
	}

	int err = devide_real_int(dividend, divisor, &division);
	switch (err)
	{
	case ERROR_OVERFLOW:
		printf("Переполнение буфера.\n");
		break;
	case ERROR_ZERO_DIVISION:
		printf("Деление на ноль.\n");
	}
	if (err != 0)
	{
		_getch();
		return -1;
	}

	
	printf("Division: \n");
	//print_real(division);

	// TODO ANSWER_NORMALISATION
	printf("\nНормализация: \n");
	//normalization_error = normalize(&division);
	//if (normalization_error != 0)
		//printf("Невозможно нормализовать получившееся число.\n");
	//if (normalization_error == 0 || 1)
	
	if(normalize_for_answer(&division) != 0)
			printf("Невозможно нормализовать получившееся число, переполнение порядка.\n");	
	else
	{

		print_grid(&division);
		print_real(division);
		printf("\n");
	}
	_getch();
	return 0;
}
