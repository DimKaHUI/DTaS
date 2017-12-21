#include <stdlib.h>
#include "hashtable.h"
#include <stdio.h>

void print_oatable(htable_oa* table, printer p)
{
	for (int i = 0; i < table->length; i++)
	{
		p(table->data[i]);
	}
}

void print_ltable(htable_l* table, printer p)
{
	for (int i = 0; i < table->length; i++)
	{
		p(table->lists[i]);
	}
}

htable_oa* create_oa(int length, hash_function f)
{
	htable_oa *table = malloc(sizeof(htable_oa));
	table->data = malloc(sizeof(float*)* length);
	for (int i = 0; i < length; i++)
		table->data[i] = NULL;
	table->func= f;
	table->length = length;
	return table;
}

htable_l* create_l(int length, hash_function f)
{
	htable_l *table = malloc(sizeof(htable_l));
	table->lists = malloc(sizeof(node_t*) * length);
	for (int i = 0; i < length; i++)
		table->lists[i] = NULL;
	table->length = length;
	table->func = f;

	return table;
}

void add_l(htable_l* table, float key)
{
	int k = table->func(&key);

	node_t *head = table->lists[k];
	if (head == NULL)
	{
		head = malloc(sizeof(node_t*));
		head->next = NULL;
		head->data = malloc(sizeof(float));
		*(float*)head->data = key;
		table->lists[k] = head;
		return;
	}

	while (head->next)
	{
		head = head->next;
	}
	head->next = malloc(sizeof(node_t*));
	head->next->next = NULL;
	head->next->data = malloc(sizeof(float));
	*(float*)head->next->data = key;
}

void add_oa(htable_oa* table, float key)
{
	int k = table->func(&key);
	while (table->data[k] != NULL)
		k++;
	table->data[k] = malloc(sizeof(float));
	*(float*)table->data[k] = key;
}

int search_hl(htable_l* table, float key)
{
	int k = table->func(&key);
	node_t *head = table->lists[k];
	while (head)
	{
		if (*(float*)head->data == key)
			return 0;
		head = head->next;
	}
	return ERROR_NOT_FOUND;
}

int search_hl_cnt(htable_l* table, float key, int* comparisons)
{
	int k = table->func(&key);
	*comparisons = 0;
	node_t *head = table->lists[k];
	while (head)
	{
		(*comparisons)++;
		if (*(float*)head->data == key)
			return 0;
		head = head->next;
	}
	return ERROR_NOT_FOUND;
}

int search_hoa(htable_oa* table, float key)
{
	int k = table->func(&key);
	while (table->data[k] != NULL)
	{
		if (*(float*)(table->data[k]) == key)
			return 0;
		k++;
	}
	return ERROR_NOT_FOUND;
}

int search_hoa_cnt(htable_oa* table, float key, int* comparisons)
{
	int k = table->func(&key);
	*comparisons = 0;
	while (table->data[k] != NULL)
	{
		(*comparisons)++;
		if (*(float*)(table->data[k]) == key)
			return 0;
		k++;
	}
	return ERROR_NOT_FOUND;
}

int meml(htable_l* t)
{
	int mem = sizeof(htable_l) + sizeof(hash_function);
	for (int i = 0; i < t->length; i++)
	{
		node_t *head = t->lists[i];
		while (head)
		{
			mem += sizeof(node_t);
			head = head->next;
		}
	}
	return mem;
}
