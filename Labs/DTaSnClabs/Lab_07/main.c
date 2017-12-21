#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mytree.h"
#include "hashtable.h"
#include <stdlib.h>
#include <intrin.h>

#define ERROR_CMD -111
#define ERROR_NOT_INITIALIZED -112
#define ERROR_ILLEGAL_SYMBOL -113
#define ERROR_NOT_BUILDED -114

#define ARR_LEN 17
#define TABLE_LEN 17

#pragma intrinsic(__rdtsc)
unsigned __int64 tick()
{
	return __rdtsc();
}

typedef unsigned long long ulong;

void float_printer(tnode *node)
{
	printf("%3.2f\n", *(float*)node->key);
}

void list_printer(void *record)
{
	node_t *head = record;
	if (head == NULL)
		printf("####");
	while (head != NULL)
	{
		printf("%3.2f ", *(float*)head->data);
		head = head->next;
	}
	printf("\n");
}

void oa_printer(void *record)
{
	if (record != NULL)
		printf("%3.2f\n", *(float*)record);
	else
		printf("####\n");
}

int float_hash(void *key)
{
	float realK = *(float*)key;
	int integral_part = (int)realK;
	float real_part = realK - integral_part;
	int real_modified = (int)(real_part * 100);
	integral_part ^= real_modified;
	return integral_part % TABLE_LEN;
}

float build_array(tnode *root, float *arr, int *pos)
{
	if (root == NULL)
	{
		return 0;
	}
	value_t *data = root->data;
	float left = 0;
	float right = 0;

	if (root->left)
	{
		left = build_array(root->left, arr, pos);
	}

	arr[*pos] = data->result;
	(*pos)++;

	if (root->right)
	{
		right = build_array(root->right, arr, pos);
	}	
	return data->result;
}

float calculate_nodes(tnode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	value_t *data = root->data;
	float left = 0;
	float right = 0;
	if (root->left)
	{
		left = calculate_nodes(root->left);
	}
	if (root->right)
	{
		right = calculate_nodes(root->right);
	}
	switch (data->operation)
	{
	case summ:
		data->result = left + right;
		return data->result;
		break;
	case prod:
		data->result = left * right;
		return data->result;
	case diff: 
		data->result = left - right;
		return data->result;
		break;
	case none: 
		return data->result;
		break;
	default: 
		return 0;
	}
}

int main(void)
{
	printf("0. Exit\n");
	printf("1. Get array\n");
	printf("2. Build binary serach tree\n");
	printf("3. Build avl tree\n");
	printf("4. Buil hash-table\n");
	printf("5. Test hash\n");
	printf("6. Compare methods\n");

	float *arr = NULL;
	tnode *binary_tree = NULL;
	tnode *avl_tree = NULL;
	htable_oa *oatable = NULL;
	htable_l *ltable = NULL;

	int err = 0;
	int cmd = -1;
	do
	{
		printf("\nInput command: ");
		fflush(stdin);
		if (scanf("%d", &cmd) != 1)
		{
			err = ERROR_CMD;
			goto error_handling;
		}

		if (cmd == 1)
		{
			tnode *expr_tree = build_expr(9, 8, 7, 6, 5, 4, 3, 2, 1);
			free(arr);
			arr = malloc(sizeof(float)* ARR_LEN);
			float result = calculate_nodes(expr_tree);
			int length = 0;
			build_array(expr_tree, arr, &length);
			printf("Result: %3.2f\n", result);
			printf("Resulting array: ");
			for (int i = 0; i < ARR_LEN; i++)
			{
				printf("%3.2f ", arr[i]);
			}
			printf("\n");
		}
		else if (cmd == 2)
		{
			if (arr == NULL)
				err = ERROR_NOT_INITIALIZED;			
			if (err != 0)
				goto error_handling;

			free_tree(binary_tree);
			binary_tree = NULL;
			for (int i = 0; i < ARR_LEN; i++)
			{
				tnode *node = malloc(sizeof(tnode));
				node->key = malloc(sizeof(float));	
				node->data = NULL;
				*((float*)node->key) = arr[i];
				node->left = NULL;
				node->right = NULL;
				binary_tree = tree_add(binary_tree, node);
			}
			printf("Resulting tree: \n");
			print_tree(binary_tree, 0, float_printer);
		}
		else if (cmd == 3)
		{
			if (arr == NULL)
				err = ERROR_NOT_INITIALIZED;
			if (err != 0)
				goto error_handling;

			free_tree(avl_tree);
			avl_tree = NULL;
			for (int i = 0; i < ARR_LEN; i++)
			{
				tnode *node = malloc(sizeof(tnode));
				node->key = malloc(sizeof(float));
				node->data = NULL;
				*((float*)node->key) = arr[i];
				node->left = NULL;
				node->right = NULL;
				node->height = 1;
				avl_tree = avl_add(avl_tree, node);
			}
			printf("Resulting tree: \n");
			print_tree(avl_tree, 0, float_printer);
		}
		else if (cmd == 4)
		{
			if (arr == NULL)
				err = ERROR_NOT_INITIALIZED;
			if (err != 0)
				goto error_handling;
			oatable = create_oa(TABLE_LEN, float_hash);
			ltable = create_l(TABLE_LEN, float_hash);
			for (int i = 0; i < ARR_LEN; i++)
			{
				add_l(ltable, arr[i]);
				add_oa(oatable, arr[i]);
			}
			printf("Table with list: \n");
			print_ltable(ltable, list_printer);
			printf("Table with open addressation:\n");
			print_oatable(oatable, oa_printer);
		}
		else if (cmd == 5)
		{
			printf("Input float value: \n");
			float val;
			if (scanf("%f", &val) != 1)
				err = ERROR_ILLEGAL_SYMBOL;
			if (err != 0)
				goto error_handling;
			int hash = float_hash(&val);
			printf("Hash: %d\n", hash);
		}
		else if (cmd == 6)
		{
			if (
				avl_tree == NULL ||
				binary_tree == NULL ||
				ltable == NULL ||
				oatable == NULL
				)
			{
				err = ERROR_NOT_BUILDED;
			}
			if (err != 0)
				goto error_handling;
			int
				cmp_binary = 0,
				cmp_avl = 0,
				cmp_hash_l = 0,
				cmp_hash_oa = 0;
			ulong
				time_binary = 0,
				time_avl = 0,
				time_hash_l = 0,
				time_hash_oa = 0;
			
			// Time
			time_binary = tick();
			for (int i = 0; i < ARR_LEN; i++)
			{
				get(binary_tree, arr[i]);
			}
			time_binary = (tick() - time_binary);// / ARR_LEN;

			time_avl = tick();
			for (int i = 0; i < ARR_LEN; i++)
			{
				get(avl_tree, arr[i]);
			}
			time_avl = (tick() - time_avl);// / ARR_LEN;

			time_hash_l = tick();
			for (int i = 0; i < ARR_LEN; i++)
			{
				search_hl(ltable, arr[i]);
			}
			time_hash_l = (tick() - time_hash_l);// / ARR_LEN;

			time_hash_oa = tick();
			for (int i = 0; i < ARR_LEN; i++)
			{
				search_hoa(oatable, arr[i]);
			}
			time_hash_oa = (tick() - time_hash_oa);// / ARR_LEN;

			// Comparisons			
			for (int i = 0; i < ARR_LEN; i++)
			{
				int tmp = 0;
				get_cnt(binary_tree, arr[i], &tmp);
				cmp_binary += tmp;
			}
			//cmp_binary /= ARR_LEN;
			for (int i = 0; i < ARR_LEN; i++)
			{
				int tmp = 0;
				get_cnt(avl_tree, arr[i], &tmp);
				cmp_avl += tmp;
			}
			//cmp_avl /= ARR_LEN;

			for (int i = 0; i < ARR_LEN; i++)
			{
				int tmp = 0;
				search_hl_cnt(ltable, arr[i], &tmp);
				cmp_hash_l += tmp;
			}
			//cmp_hash_l /= ARR_LEN;

			for (int i = 0; i < ARR_LEN; i++)
			{
				int tmp = 0;
				search_hoa_cnt(oatable, arr[i], &tmp);
				cmp_hash_oa += tmp;
			}
			//cmp_hash_oa /= ARR_LEN;

			printf("Time of binary tree searching: %3.2f\n", (double)(time_binary) / ARR_LEN);
			printf("Time of avl tree searching: %3.2f\n", (double)time_avl / ARR_LEN);
			printf("Time of searching in hash table with list: %3.2f\n", (double)time_hash_l / ARR_LEN);
			printf("Time of searching in hash table with open addressation: %3.2f\n", (double)time_hash_oa / ARR_LEN);
			printf("Comparisons in binary tree: %3.2f\n", (double)cmp_binary / ARR_LEN);
			printf("Comparisons in avl tree: %3.2f\n", (double)cmp_avl / ARR_LEN);
			printf("Comparisons in hash table with list: %3.2f\n", (double)cmp_hash_l/ARR_LEN);
			printf("Comparisons in hash table with open addressation: %3.2f\n", (double)cmp_hash_oa / ARR_LEN);
		
			ulong mem_tree = (sizeof(tnode) + sizeof(float*) - sizeof(void*))* ARR_LEN;
			ulong mem_hashl = meml(ltable);
			ulong mem_hashoa = sizeof(htable_oa)+sizeof(float*)* ARR_LEN;

			printf("Memory of trees: %llu\n", mem_tree);
			printf("Memory of hash table with list: %llu\n", mem_hashl);
			printf("Memory of hash table with open addressation: %llu\n", mem_hashoa);
		}
		else if (cmd != 0)
			err = ERROR_CMD;

error_handling:
		switch (err)
		{
		case ERROR_CMD:
			printf("Error with reading command.\n");
			break;
		case ERROR_NOT_INITIALIZED:
			printf("Run array building first!\n");
			break;
		default:;			
		}

		err = 0;
	} while (cmd);
	return 0;
}