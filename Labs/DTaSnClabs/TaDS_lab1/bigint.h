#ifndef BIGINT_H
#define BIGINT_H

#define BIGINT_SIZE 30
#define ERROR_BIGINT_IO 99
#define ERROR_NO_SIGN -110
#define ERROR_TOO_BIG_INT 101

struct BigInt
{
	int size;
	char Num[BIGINT_SIZE + 1];

	// Чэръ (-1 or 1)
	char sign;
};

typedef struct BigInt bigint_t;

int read_big_int(bigint_t *big_int, int size);

int read_int_from_line(bigint_t *big_int);

void print_int(bigint_t big_int);

int compare(bigint_t a, bigint_t b);

bigint_t summ(bigint_t a, bigint_t b);

bigint_t get_zero_int();

bigint_t negate(bigint_t a);

bigint_t modulo(bigint_t dividend, bigint_t divisor);

void big_div(bigint_t dividend, bigint_t divisor, int *div_res, bigint_t *mod_res);

bigint_t prod(bigint_t num, int count);

bigint_t append(bigint_t num, char d);

int append_int(bigint_t *num, int i);

#endif // BIGINT_H
