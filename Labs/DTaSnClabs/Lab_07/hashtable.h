#pragma once

#define ERROR_NOT_FOUND -11

#define MAX_COMPARISONS 4

typedef int (*hash_function)(void*);
typedef void(*printer)(void*);

typedef struct htable_open_address
{
	int length;
	void **data;
	hash_function func;
} htable_oa;

typedef struct node
{
	void *data;
	struct node *next;
}node_t;

typedef struct htable_list
{
	int length;
	node_t **lists;
	hash_function func;
} htable_l;

void print_oatable(htable_oa *table, printer p);
void print_ltable(htable_l *table, printer p);

htable_oa *create_oa(int length, hash_function f);
htable_l *create_l(int length, hash_function f);

void add_l(htable_l *table, float key);
void add_oa(htable_oa *table, float key);
int search_hl(htable_l *table, float key);
int search_hl_cnt(htable_l *table, float key, int *comparisons);
int search_hoa(htable_oa *table, float key);
int search_hoa_cnt(htable_oa *table, float key, int *comparisons);

int meml(htable_l *t);