#define _CRT_SECURE_NO_WARNINGS

#include "mytree.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define EPS 0.001
#define ERROR_ILLEGAL_SYMBOL -111
#define ERROR_UNKNOWN_CMD -121

#define RANDINT(min, max) min + rand() % max


tnode *get_double(tnode *tree, double value)
{
	if (fabs(*(double*)(tree->data) - value) < EPS)
	{
		return tree;
	}
	tnode *left_res = NULL;
	if (tree->left)
		left_res = get_double(tree->left, value);
	if (left_res != NULL)
	{
		return left_res;
	}
	tnode *right_res = NULL;
	if (tree->right)
		right_res = get_double(tree->right, value);
	if (right_res != NULL)
		return right_res;
	return NULL;
}

void printer(tnode *n)
{
	if (((value_t*)(n->data))->operation == none)
	{
		printf("%3.2f\n", ((value_t*)(n->data))->result);
	}
	if (((value_t*)(n->data))->operation == summ)
	{
		printf("+\n");
	}
	if (((value_t*)(n->data))->operation == prod)
	{
		printf("*\n");
	}
	if (((value_t*)(n->data))->operation == diff)
	{
		printf("-\n");
	}
}

tnode *gen_random(int nodes)
{
	struct tnode *root = NULL;
	for (int i = 0; i < nodes; i++)
	{
		tnode *node = malloc(sizeof(tnode));
		node->data = malloc(sizeof(double));
		*(double*)(node->data) = RANDINT(1, nodes * 2) * 2.0f;
		node->key = RANDINT(1, nodes * 4);
		node->left = NULL;
		node->right = NULL;
		root = tree_add(root, node);
	}
	return root;
}

void dprint(tnode *n)
{
	printf("%2.2d:%3.2f\n", n->key, *(double*)n->data);
}

float calculate(tnode *n)
{
#ifndef SHOW_CALCULATIONS
	switch (((value_t*)(n->data))->operation)
	{
	case summ:
		return calculate(n->left) + calculate(n->right);
	case prod:
		return calculate(n->left) * calculate(n->right);
	case diff:
		return  calculate(n->left) - calculate(n->right);
	default:
		return ((value_t*)(n->data))->result;
	}
#else
	if (n->data->operation == none)
	{
		printf("Return %3.2f\n", n->data->result);
		return n->data->result;
	}
	float left = calculate(n->left);
	float right = calculate(n->right);
	if (n->data->operation == summ)
	{		
		printf("%3.2f + %3.2f\n", left, right);
		return left + right;
	}
	if (n->data->operation == prod)
	{
		printf("%3.2f * %3.2f\n", left, right);
		return left * right;
	}
	if (n->data->operation == diff)
	{
		printf("%3.2f - %3.2f\n", left, right);
		return left - right;
	}
	printf("Error!\n");
	return 0;
#endif
}

int main(void)
{	
	srand(time(NULL));

	printf("1. Calculate expression, print it's tree and compare with stack\n");
	printf("2. Add to tree\n");
	printf("3. Remove from tree\n");
	printf("4. Print tree\n");
	printf("5. Generate random tree\n");
	printf("6. Search for value\n");
	printf("7. Search for key\n");
	printf("8. Analize efficiency of sorting and searching\n");

		
	tnode *tree = NULL;

	int cmd = -1;
	int err = 0;
	do
	{
		printf("Input command: ");
		fflush(stdin);
		if (scanf("%d", &cmd) != 1)
		{
			err = ERROR_ILLEGAL_SYMBOL;
			cmd = -1;
		}

		if (cmd == -1 || cmd == 0)
		{

		}
		else if (cmd == 1)
		{

			float a, b, c, d, e, f, g, h, i;
			printf("Input values for A, B, ... , I\n");
			if (scanf("%f %f %f %f %f %f %f %f %f", &a, &b, &c, &d, &e, &f, &g, &h, &i) != 9)
			{
				err = ERROR_ILLEGAL_SYMBOL;
			}
			else
			{
				tnode *expr = NULL;
				expr = build_expr(a, b, c, d, e, f, g, h, i);
				print_tree_expr(expr, 0, printer);
				float res = calculate(expr);
				printf("Result of calculation: %3.2f\n", res);
				float check = a + (b * (c + (d * (e + f) - (g - h)) + i));
				if (fabs(res - check) <= EPS)
					printf("Result is correct!\n");
				else
					printf("Correct result: %3.2f\n", check);
			}
		}
		else if (cmd == 2)
		{
			err = 0;
			printf("Adding element to the tree\n");
			printf("Input the key (integer) and value (double): \n");
			int key;
			double value;
			if (scanf("%d %lf", &key, &value) != 2)
			{
				err = ERROR_ILLEGAL_SYMBOL;
			}
			else
			{
				tnode *node = malloc(sizeof(tnode));
				node->data = malloc(sizeof(double));
				*(double*)(node->data) = value;
				node->key = key;
				node->left = NULL;
				node->right = NULL;
				tree = tree_add(tree, node);
			}
		}
		else if (cmd == 3)
		{
			err = 0;
			printf("Removing element from the tree\n");
			printf("Input the key (integer): \n");
			int key;
			if (scanf("%d", &key) != 1)
			{
				err = ERROR_ILLEGAL_SYMBOL;
			}
			else
			{
				tnode *removed;
				tree_remove(&tree, key, &removed);
			}
		}
		else if (cmd == 4)
		{
			err = 0;
			print_tree(tree, 0, dprint);
		}
		else if (cmd == 5)
		{
			err = 0;
			printf("Generating random tree\n");
			printf("Input number of nodes: \n");
			int num;
			if (scanf("%d", &num) != 1)
			{
				err = ERROR_ILLEGAL_SYMBOL;
			}
			else
			{
				free_tree(tree);
				tree = gen_random(num);
			}
		}
		else if (cmd == 6)
		{
			err = 0;
			printf("Searching for value\n");
			printf("Input value (double): \n");
			double value;
			if (scanf("%lf", &value) != 1)
			{
				err = ERROR_ILLEGAL_SYMBOL;
			}
			else
			{
				tnode *res = get_double(tree, value);
				if (res == NULL)
					printf("Not found!\n");
				else
					printf("Key is %d\n", res->key);
			}
		}
		else if (cmd == 7)
		{
			err = 0;
			printf("Searching for key\n");
			printf("Input key (integer): \n");
			int key;
			if (scanf("%d", &key) != 1)
			{
				err = ERROR_ILLEGAL_SYMBOL;
			}
			else
			{
				tnode *res = get(tree, key);
				if (res == NULL)
					printf("Not found!\n");
				else
					printf("Value is %lf\n", *(double*)(res->data));
			}
		}
		else
			err = ERROR_UNKNOWN_CMD;

	} while (cmd != 0);
}
