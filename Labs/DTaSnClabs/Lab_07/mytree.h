#pragma once

typedef unsigned long long ulong;

enum operation_type                // Тип операции
{
	summ, prod, diff, none
};

typedef struct value_t             // Данные, которые хранит узел дерева
{
	enum operation_type operation;
	float result;
}value_t;

typedef struct tnode               // Узел дерева
{	
	unsigned char height;
	void *key;
	void *data;
	struct tnode *left;
	struct tnode *right;	
} tnode;

typedef void(*method_t)(tnode*);
typedef int(*comparator)(tnode*);

// Построение выражения для дерева
tnode *build_expr(float a, float b, float c, float d, float e, float f, float g, float h, float i);

void free_tree(tnode *n);                                    // Освобождение памяти, выделенной под дерево
void print_tree(tnode *n, int level, method_t printer);      // Печать дерева, которое хранит числовые значения

void traverse_postfix(tnode *root, method_t action);         // Пост фиксный обход
void traverse_infix(tnode *root, method_t action);           // Инфиксный обход
void traverse_prefix(tnode *root, method_t action);          // Префиксный обход
float calculate(tnode* root);                                // Вычисление выражения

tnode *tree_add(tnode *root, tnode *node);                   // Добавление узла в дерево
void tree_remove(tnode** root, int k, tnode** removed);      // Удаление узла из дерева
tnode *get(tnode *tree, float k);                            // Поиск узла по ключу
tnode *get_val(tnode *tree, void* value);                    // Поиск узла по значению

// Для АВЛ деревьев
tnode *avl_add(tnode *root, tnode *node);                   // Добавление узла в дерево

tnode *get_cnt(tnode *tree, float k, int *comparisons);      // Поиск узла по ключу