#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mytree.h"
#include <stdlib.h>

#define ERROR_CMD -111
#define ERROR_NOT_INITIALIZED -112

void float_printer(tnode *node)
{
	printf("%3.2f\n", *(float*)node->key);
}

float build_array(tnode *root, float *arr, int pos)
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
		pos++;
	}

	arr[pos] = data->result;
	pos++;

	if (root->right)
	{
		right = build_array(root->right, arr, pos);
		pos++;
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

	float *arr = NULL;
	tnode *avl_tree = NULL;

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
			arr = malloc(sizeof(float) * 7);
			float result = calculate_nodes(expr_tree);
			build_array(expr_tree, arr, 0);
			printf("Result: %3.2f\n", result);
			printf("Resulting array: ");
			for (int i = 0; i < 7; i++)
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
			for (int i = 0; i < 7; i++)
			{
				tnode *node = malloc(sizeof(tnode));
				node->key = malloc(sizeof(float));	
				node->data = NULL;
				*((float*)node->key) = arr[i];
				node->left = NULL;
				node->right = NULL;
				avl_tree = tree_add(avl_tree, node);
			}
			printf("Resulting tree: \n");
			print_tree(avl_tree, 0, float_printer);
		}
		else
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