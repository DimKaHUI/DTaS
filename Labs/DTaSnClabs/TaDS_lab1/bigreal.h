#ifndef BIGREAL_H
#define BIGREAL_H

#include "bigint.h"

#define EXP_BASE 10
#define MANTISSA_MAX_SIZE 30
#define ORDER_MAX 99999
#define ORDER_MAX_SIZE 5

// Errors
#define ERROR_OVERFLOW -1
#define ERROR_BIGREAL_IO -101
#define ERROR_TOO_LARGE_ORDER -102
#define ERROR_ARGUMENT_EXCEPTION -103
#define ERROR_TOO_LARGE_MANTISSA -104
#define ERROR_ZERO_DIVISION -105
#define ERROR_DOT_AFTER_E -106
#define ERROR_TOO_MANY_E -107
#define ERROR_TOO_MANY_DOTS -108
#define ERROR_ILLEGAL_FORMAT -109
#define ERROR_NO_SIGN -110
#define ERROR_TOO_MANY_SIGNS -111
#define ERROR_SIGN_INSIDE_NUMER -112

struct BigReal
{
	// Порядок
	int p;

	// Мантисса
	//char M[MANTISSA_MAX_SIZE];
	bigint_t M;

	// Позиция точки в мантиссе
	char floating_point_pos;
};

typedef struct BigReal bigreal_t;

// Деление вещественное на целое число
int devide_real_int(bigreal_t dividend, bigint_t big_int, bigreal_t* result);

bigreal_t get_zero_real();

// Вывод вещественного на экран
void print_real(bigreal_t real);

void print_grid(const bigreal_t *real);

// Поразрядный ввод вещественного числа
int read_big_real(bigreal_t *real, int m_len);

int read_real_from_line(bigreal_t *real);

int normalize(bigreal_t *real);

int normalize_for_answer(bigreal_t *real);

#endif // BIGREAL_H
