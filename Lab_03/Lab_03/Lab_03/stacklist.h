#pragma once

// List-based stack
#define STAK_LIST_MAXSIZE 5

// Error codes
#define ERROR_ALLOCATION_ERROR -21
#define ERROR_STACK_LIST_EMPTY -22
#define ERROR_STACK_LIST_OVERFLOW -23

typedef struct ListUnit
{
	int val;
	struct ListUnit *prev;
} ListUnit;


int liststack_add(ListUnit **stack, int a);           // Добавляет элемент в списочный стек
int liststack_remove(ListUnit **stack, int *result);  // Удаляет элемент из списочного стека
int liststack_is_empty(ListUnit **stack);             // Проверяет, является ли списочный стек пустым
void liststack_create(ListUnit**);                    // Инициализирует пустой стек