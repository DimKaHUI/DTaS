#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "bigreal.h"
#include "assert.h"
#include "bigint.h"

#define LINE_LEN MANTISSA_MAX_SIZE + 10

bigreal_t get_zero_real()
{
	bigreal_t real;
	real.M = get_zero_int();
	real.p = 0;
	real.floating_point_pos = 0;
	return real;
}



// Вывод вещественного на экран
void print_real(bigreal_t real)
{
	bigint_t mantissa = real.M;

	if (mantissa.sign == -1)
	{
		printf("-");
	}
	if (real.floating_point_pos >= mantissa.size)
	{
		printf("%d", 0);
		printf(".");
		int zeros = real.floating_point_pos - mantissa.size;
		for (int i = 0; i < zeros; i++)
			printf("%d", 0);
	}

	for (int i = mantissa.size - 1; i >= 0; i--)
	{
		printf("%d", (int)mantissa.Num[i]);
		if (real.floating_point_pos == i)
			printf(".");
	}
	printf("E");
	printf("%d", real.p);
}

void print_grid(const bigreal_t* real)
{
	bigint_t mantissa = real->M;
	// Drawing grid
	int cnum = 1;
	if (mantissa.sign == -1)
	{
		printf(" ");
	}
	if (real->floating_point_pos >= mantissa.size)
		printf(" ");
	for (int i = 0; i < mantissa.size; i++)
	{
		if (i != mantissa.size - real->floating_point_pos)
		{
			if (cnum % 10 == 0)
			{
				printf("%d", cnum / 10);
			}
			else
				printf("-");
			cnum++;
		}
		else
			printf(" ");
	}
	printf("\n");

}

// Ввод вещественного числа
int read_big_real(bigreal_t *real, int size)
{
	if (real == NULL)
	{
		printf("Argument exception. Real must be not NULL");
		return ERROR_ARGUMENT_EXCEPTION;
	}

	if (size > MANTISSA_MAX_SIZE || size <= 0)
	{
		printf("Mantissa length must be inside [0, %d]", MANTISSA_MAX_SIZE);
		return ERROR_TOO_LARGE_MANTISSA;
	}

	int err = read_big_int(&(real->M), size) != 0;
	if (err != 0)
		return err;
	printf("Input amount of digits, placed to the RIGHT of the floating point: ");
	int pos;
	if (scanf("%d", &pos) != 1)
	{
		printf("Illegal input.");
		return ERROR_BIGREAL_IO;
	}
	real->floating_point_pos = pos;

	int order;
	printf("Input order: ");
	if (scanf("%d", &order) != 1)
	{
		printf("Illegal input.");
		return ERROR_BIGREAL_IO;
	}

	if (order > ORDER_MAX || order < -ORDER_MAX)
	{
		printf("Order must be in bounds [%d, %d]", -ORDER_MAX, ORDER_MAX);
		return ERROR_TOO_LARGE_ORDER;
	}

	real->p = order;

	return 0;
}

int read_real_from_line(bigreal_t* real)
{
	char line[LINE_LEN];
	if (gets_s(line, LINE_LEN) == NULL)
		return ERROR_BIGREAL_IO;
	real->M = get_zero_int();
	real->M.size = 0;

	if (line[0] == '-')
		real->M.sign = -1;
	else if (line[0] == '+')
		real->M.sign = 1;
	else
		return ERROR_NO_SIGN;

	// Counting E and Dot
	int
		e_count = 0,
		dot_count = 0,
		sign_count = 0,
		e_after_dot = 1,
		i = 1,
		e_pos = -1,
		dot_pos = -1;
	while (line[i] != '\0')
	{
		if (line[i] == 'E' || line[i] == 'e')
		{
			e_count++;
			e_pos = i;
			if (e_count > 1)
				return ERROR_TOO_MANY_E;
		}
		if (line[i] == '.')
		{
			dot_count++;
			dot_pos = i;
			if (e_count > 0)
				return ERROR_DOT_AFTER_E;
			if (dot_count > 1)
				return ERROR_TOO_MANY_DOTS;
		}
		if (line[i] == '-')
		{
			sign_count++;
			if (sign_count > 1)
				return ERROR_TOO_MANY_SIGNS;
			if (e_count != 1)
				return ERROR_SIGN_INSIDE_NUMER;
			if (i != e_pos + 1)
				return ERROR_SIGN_INSIDE_NUMER;
		}
		if (
			line[i] != '0' &&
			line[i] != '1' &&
			line[i] != '2' &&
			line[i] != '3' &&
			line[i] != '4' &&
			line[i] != '5' &&
			line[i] != '6' &&
			line[i] != '7' &&
			line[i] != '8' &&
			line[i] != '9' &&
			line[i] != 'E' &&
			line[i] != 'e' &&
			line[i] != '.' &&
			line[i] != '-')
		{
			return ERROR_BIGREAL_IO;
		}

		i++;
	}

	if (e_pos == -1)
		return ERROR_ILLEGAL_FORMAT;
	if (dot_pos == -1)
		return ERROR_ILLEGAL_FORMAT;

	// Writing mantissa
	i = e_pos - 1;
	int pos = 0;
	while (i > 0)
	{
		if (line[i] == '.')
		{
			real->floating_point_pos = e_pos - i - 1;
			pos--;
		}
		else
		{
			char symbol = line[i];
			real->M.Num[pos] = atoi(&symbol);
			real->M.size++;
			//printf("В M.Num[%d] записано %d, символ номер %d (сомвол <%d>) в строке\n", pos, real->M.Num[pos], i, symbol);
			if (real->M.size > BIGINT_SIZE)
				return ERROR_TOO_LARGE_MANTISSA;
		}
		i--;
		pos++;
	}

	i = e_pos + 1;
	if (line[i] == '\0')
	{
		printf("End of line reached.\n");
		real->p = 0;
		return 0;
	}
	pos = 0;
	char exp[ORDER_MAX_SIZE];
	while (line[i] != '\0')
	{
		if (pos >= ORDER_MAX_SIZE)
			return ERROR_TOO_LARGE_ORDER;
		exp[pos] = line[i];
		i++;
		pos++;
	}
	real->p = atoi(exp);
	return 0;

}

int check_if_zero(const bigint_t *big_int)
{
	for (int i = 0; i < big_int->size; i++)
	{
		if (big_int->Num[i] != 0)
			return 0;
	}
	return 1;
}

int normalize(bigreal_t *real)
{
	// |ZEROS|
	if (check_if_zero(&real->M) == 1)
	{
		real->p = 0;
		return 0;
	}

	int L = real->floating_point_pos;
	//int K = real->M.size - 1;
	int K;
	for (K = real->M.size - 1; K >= 0 && real->M.Num[K] == 0; K--);

	//printf("\nL = %d, K = %d\n", L, K);
	int offset = L - K;

	if (real->p - offset > ORDER_MAX || real->p - offset < -ORDER_MAX)
		return -1;

	real->p -= offset;
	real->floating_point_pos = K;

	// removing zeros from right
	int pos = 0;
	while (real->M.Num[pos] == 0 && real->floating_point_pos >= pos)
	{
		for (int i = 0; i < real->M.size; i++)
		{
			real->M.Num[i] = real->M.Num[i + 1];
		}
		real->floating_point_pos--;
		real->M.size--;
	}

	for (int i = real->M.size - 1; i >= 0 && real->M.Num[i] == 0; i--)
	{
		real->M.size--;
	}

	return 0;

}

int normalize_for_answer(bigreal_t* real)
{
	real->floating_point_pos++;
	real->p++;
	return 0;
}

int round_up(bigint_t *number)
{
	number->Num[0]++;
	for (int i = 0; i < number->size - 1 && number->Num[i] >= 10; i++)
	{
		number->Num[i] -= 10;
		number->Num[i + 1]++;
	}
	if (number->Num[number->size - 1] >= 10)
	{
		number->Num[number->size - 1] -= 10;
		number->size++;
		if (number->size > BIGINT_SIZE)
			return ERROR_OVERFLOW;
		number->Num[number->size - 1] = 1;
	}
	return 0;
}


// Деление вещественного на целое число
int devide_real_int(bigreal_t dividend, bigint_t divisor, bigreal_t* result)
{
	int sign = dividend.M.sign * divisor.sign;
	dividend.M.sign = 1;
	divisor.sign = 1;
	bigreal_t division = get_zero_real();
	division.p = dividend.p;

	// Check if dividend or divisor are zero
	if (check_if_zero(&divisor) == 1)
	{
		return ERROR_ZERO_DIVISION;
	}

	if (check_if_zero(&dividend.M))
	{
		*result = division;
		return 0;
	}
	
	bigint_t mod = get_zero_int();
	int mantissa_current = 0;	
	int current_iteration = 0;
	do
	{
		int count_of_appendings = 0;
		// Constructing mod
		while (compare(mod, divisor) == -1)
		{
			if (count_of_appendings > 0 && current_iteration > 0)
			{
				append_int(&division.M, 0);
			}
			if (mantissa_current < dividend.M.size)
			{
				append_int(&mod, dividend.M.Num[dividend.M.size - mantissa_current - 1]);
			}
			else if (!check_if_zero(&mod))
			{
				append_int(&mod, 0);
			}
			else
				goto cycle_exit;
			if (dividend.M.size - mantissa_current <= dividend.floating_point_pos)
				division.p--;
			mantissa_current++;
			count_of_appendings++;			
		}

		int div_res;
		bigint_t mod_res = get_zero_int();
		big_div(mod, divisor, &div_res, &mod_res);
		if (division.M.size < MANTISSA_MAX_SIZE)
			append_int(&division.M, div_res);
		else
		{
			int err = 0;
			if (div_res >= 5)
				err = round_up(&division.M);
			if (err != 0)
				return ERROR_OVERFLOW;
			normalize(&division);
			if (division.M.size >= MANTISSA_MAX_SIZE)
				goto cycle_exit;
		}
		mod = mod_res;

		normalize(&division);

		current_iteration++;
	} while (division.M.size <= MANTISSA_MAX_SIZE);

	cycle_exit:

	division.M.sign = sign;
	*result = division;
	return 0;
}

