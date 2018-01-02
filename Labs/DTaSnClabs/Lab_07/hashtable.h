#pragma once

#define ERROR_NOT_FOUND -11

#define MAX_COMPARISONS 4

typedef int (*hash_function)(void*);
typedef void(*printer)(void*);

typedef struct htable_open_address  // Хеш таблица с открытой адресацией
{
	int length;
	void **data;
	hash_function func;
} htable_oa;

typedef struct node                 // Узел списка
{
	void *data;
	struct node *next;
}node_t;

typedef struct htable_list          // Хеш таблица, основанная на списках
{
	int length;
	node_t **lists;
	hash_function func;
} htable_l;

void print_oatable(htable_oa *table, printer p);                   // Печать таблицы с открытой адресацией
void print_ltable(htable_l *table, printer p);                     // Печать таблицы на списках

htable_oa *create_oa(int length, hash_function f);                 // Инициализация таблицы с открытой адресацией
htable_l *create_l(int length, hash_function f);                   // Инициализация таблицы на списках

void add_l(htable_l *table, float key);                            // Добавление элемента в таблицу на списках
void add_oa(htable_oa *table, float key);                          // Добавление элемента в таблицу с открытой адресацией
int search_hl(htable_l *table, float key);                         // Поиск элемента в таблице на списках
int search_hl_cnt(htable_l *table, float key, int *comparisons);   // Подсчет количества сравнений в таблице на списках
int search_hoa(htable_oa *table, float key);                       // Поиск элемента в таблице c открытой адресацией
int search_hoa_cnt(htable_oa *table, float key, int *comparisons); // Подсчет количества сравнений в таблице с открытой адресацией

int meml(htable_l *t);