#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "bigint.h"
#include <assert.h>
#include "math.h"
#include <stdlib.h>

int read_big_int(bigint_t *big_int, int size)
{
	if (size > BIGINT_SIZE || size <= 0)
	{
		printf("Size of bigint must be inside [0, %d]\n", BIGINT_SIZE);
		return ERROR_BIGINT_IO;
	}

	printf("sign (-1 for minus 1 plus): ");
	int sign;
	if (scanf("%d", &sign) == 1)
	{
		if (sign == -1 || sign == 1)
			big_int->sign = sign;
		else
		{
			big_int->sign = 1;
			fprintf(stderr, "WARNING: Unrecognized sign value. Sign will be PLUS by default.\n");
		}
	}

	for (int i = 0; i < size; i++)
	{
		int num;
		printf("digit #%d: ", i + 1);
		if (scanf("%d", &num) == 1)
		{
			if (num <= 9 && num >= 0)
				(*big_int).Num[size - i - 1] = num;
			else
			{
				fprintf(stderr, "Digit must be inside [0, 9] \n");
				i--;
			}
		}
		else
		{
			fprintf(stderr, "Illegal symbol, repeat input \n");
			i--;
		}
	}
	for (int i = size; i < BIGINT_SIZE; i++)
	{
		(*big_int).Num[i] = 0;
	}

	(*big_int).size = size;

	return 0;
}

int read_int_from_line(bigint_t *big_int)
{

	char line[BIGINT_SIZE + 1];
	gets_s(line, BIGINT_SIZE + 1);
	*big_int = get_zero_int();
	big_int->size = 0;

	if (line[0] == '-')
		big_int->sign = -1;
	else if (line[0] == '+')
		big_int->sign = 1;
	else
		return ERROR_NO_SIGN;

	int i = 1;
	while (line[i] != '\0')
	{
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
			line[i] != '9')
		{
			return ERROR_BIGINT_IO;
		}

		i++;
	}

	// Writing mantissa
	int pos = 0;
	i--;
	while (i > 0)
	{
		char symbol = line[i];
		big_int->Num[pos] = atoi(&symbol);
		big_int->size++;

		if (big_int->size > BIGINT_SIZE)
			return ERROR_TOO_BIG_INT;
		i--;
		pos++;
	}

	return 0;
}

void print_int(bigint_t big_int)
{
	if (big_int.sign == -1)
		printf("-");
	for (int i = big_int.size - 1; i >= 0; i--)
	{
		printf("%d", (int)big_int.Num[i]);
	}
}

int compare(bigint_t a, bigint_t b)
{
	if (a.sign > b.sign)
		return 1;
	if (a.sign < b.sign)
		return -1;

	if (a.sign == 1)
	{
		if (a.size > b.size)
			return 1;
		if (a.size < b.size)
			return -1;
	}
	else
	{
		if (a.size < b.size)
			return 1;
		if (a.size > b.size)
			return -1;
	}

	for (int i = a.size - 1; i >= 0; i--)
	{
		if (a.Num[i] > b.Num[i])
			return 1;
		if (a.Num[i] < b.Num[i])
			return -1;
	}

	return 0;
}

/*int max(int a, int b)
{
	if (a >= b)
		return a;
	return b;
}*/

bigint_t get_zero_int()
{
	bigint_t zero;
	zero.sign = 1;
	zero.size = 1;
	for (int i = 0; i < BIGINT_SIZE; i++)
		zero.Num[i] = 0;
	return zero;
}

bigint_t subtract(bigint_t a, bigint_t b)
{
	assert(a.sign == 1 && b.sign == 1);
	assert(compare(a, b) == 1 || compare(a, b) == 0);

	if (compare(a, b) == 0)
		return get_zero_int();

	int steps = max(a.size, b.size);

	bigint_t res = a;

	// Going through every digit (from the right side to the left)
	for (int i = 0; i < steps; i++)
	{
		if (res.Num[i] >= b.Num[i])
			res.Num[i] -= b.Num[i];
		else
		{
			if (i + 1 < steps)
				res.Num[i + 1]--;
			else
			{
				// TODO if next digit is after the last one
			}
			res.Num[i] += 10 - b.Num[i];
		}
	}

	// Resize
	for (int i = res.size - 1; i > 0; i--)
	{
		if (res.Num[i] == 0)
			res.size--;
		else
			break;
	}

	//for(int i = res.size - 1; i > 0)
	if (res.size == 1 && res.Num[0] == 0)
		res.sign = 1;
	return res;
}


bigint_t summ(bigint_t a, bigint_t b)
{
	bigint_t res = get_zero_int();
	int steps = max(a.size, b.size);
	res.size = steps;

	if (a.sign * b.sign > 0)
	{
		for (int i = 0; i < steps; i++)
		{
			int s = a.Num[i] + b.Num[i];
			if (s + res.Num[i] >= 10)
			{
				s -= 10;
				if (i + 1 >= steps)
					res.size++;
				res.Num[i + 1]++;
			}

			res.Num[i] += s;
		}

		if (a.sign == -1)
			res.sign = -1;
		return res;
	}

	// If only one of number is negative

	//  if b < 0
	if (b.sign == -1)
	{
		b.sign = 1;
		if (compare(a, b) == 1)
		{
			res = subtract(a, b);
		}
		else
		{
			res = subtract(b, a);
			res.sign = -1;
		}
	}

	// if a < 0
	if (a.sign == -1)
	{
		a.sign = 1;
		if (compare(a, b) == 1)
		{
			res = subtract(a, b);
		}
		else
		{
			res = subtract(b, a);
			res.sign = -1;
		}

		res.sign = -res.sign;
	}

	return res;
}

bigint_t negate(bigint_t a)
{
	a.sign *= -1;
	return a;
}

bigint_t prod(bigint_t num, int count)
{
	bigint_t init = num;
	if (count == 0)
		return get_zero_int();
	for (int i = 0; i < count; i++)
	{
		num = summ(num, init);
	}
	if (count < 0)
	{
		num.sign = -num.sign;
	}
	return num;
}

bigint_t append(bigint_t num, char d)
{
	if (num.size == 1 && num.Num[0] == 0)
	{
		num.Num[0] = d;
		return num;
	}

	num.size++;
	for (int i = num.size - 1; i > 0; i--)
	{
		num.Num[i] = num.Num[i - 1];
	}
	num.Num[0] = d;

	return num;
}

int append_int(bigint_t *num, int i)
{
	//bigint_t res = *num;
	if (i == 0)
	{
		*num = append(*num, (char)0);
	}
	while (i > 0)
	{
		int m = i % 10;
		if (num->size < BIGINT_SIZE)
			*num = append(*num, (char)m);
		else
			return -1;
		i = i / 10;
	}
	return 0;
}

bigint_t concatenate_bigints(bigint_t a, bigint_t b)
{
	b.size = a.size + b.size;
	for (int i = 0; i < a.size; i++)
	{
		b.Num[i + b.size] = a.Num[i];
	}
	return b;
}


void big_div(bigint_t dividend, bigint_t divisor, int *div_res, bigint_t *mod_res)
{
	dividend.sign = 1;
	divisor.sign = 1;
	if (compare(dividend, divisor) == 0) // Частный случай равенства
	{
		*div_res = 1;
		*mod_res = get_zero_int();
		return;
	}

	if (compare(dividend, divisor) == -1) // Частный случай, делимое меньше делимого
	{
		*div_res = 0;
		*mod_res = dividend;
		return;
	}

	int mult = 0;
	bigint_t division = get_zero_int();

	while (compare(division, dividend) != 1) // пока частное меньше или равно делимому
	{
		mult++;
		division = summ(division, divisor);
	}

	if (mult == 1)
	{
		*div_res = 0;
	}
	else
	{
		*div_res = mult - 1;
	}

	*mod_res = summ(dividend, negate(summ(division, negate(divisor))));
	if (mod_res->Num[mod_res->size - 1] == 0 && mod_res->size == 2)
		mod_res->size--;
	if (mod_res->size == 1 && mod_res->Num[0] == 0)
		mod_res->sign = 1;
}
