#include "mytree.h"
#include <stdlib.h>
#include <stdio.h>

tnode *build_expr(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	tnode *A = malloc(sizeof(tnode));
	A->data = malloc(sizeof(struct value_t));
	((value_t*)(A->data))->result = a;
	((value_t*)(A->data))->operation = none;
	A->right = NULL;
	A->left = NULL;
	tnode *B = malloc(sizeof(tnode));
	B->data = malloc(sizeof(struct value_t));
	((value_t*)(B->data))->result = b;
	((value_t*)(B->data))->operation = none;
	B->right = NULL;
	B->left = NULL;
	tnode *C = malloc(sizeof(tnode));
	C->data = malloc(sizeof(struct value_t));
	((value_t*)(C->data))->result = c;
	((value_t*)(C->data))->operation = none;
	C->right = NULL;
	C->left = NULL;
	tnode *D = malloc(sizeof(tnode));
	D->data = malloc(sizeof(struct value_t));
	((value_t*)(D->data))->result = d;
	((value_t*)(D->data))->operation = none;
	D->right = NULL;
	D->left = NULL;
	tnode *E = malloc(sizeof(tnode));
	E->data = malloc(sizeof(struct value_t));
	((value_t*)(E->data))->result = e;
	((value_t*)(E->data))->operation = none;
	E->right = NULL;
	E->left = NULL;
	tnode *F = malloc(sizeof(tnode));
	F->data = malloc(sizeof(struct value_t));
	((value_t*)(F->data))->result = f;
	((value_t*)(F->data))->operation = none;
	F->right = NULL;
	F->left = NULL;
	tnode *G = malloc(sizeof(tnode));
	G->data = malloc(sizeof(struct value_t));
	((value_t*)(G->data))->result = g;
	((value_t*)(G->data))->operation = none;
	G->right = NULL;
	G->left = NULL;
	tnode *H = malloc(sizeof(tnode));
	H->data = malloc(sizeof(struct value_t));
	((value_t*)(H->data))->result = h;
	((value_t*)(H->data))->operation = none;
	H->right = NULL;
	H->left = NULL;
	tnode *I = malloc(sizeof(tnode));
	I->data = malloc(sizeof(struct value_t));
	((value_t*)(I->data))->result = i;
	((value_t*)(I->data))->operation = none;
	I->right = NULL;
	I->left = NULL;
	
	tnode *diff1 = malloc(sizeof(tnode));
	diff1->data = malloc(sizeof(struct value_t));
	((value_t*)(diff1->data))->operation = diff;
	diff1->left = G;
	diff1->right = H;
	tnode *summ1 = malloc(sizeof(tnode));
	summ1->data = malloc(sizeof(struct value_t));
	((value_t*)(summ1->data))->operation = summ;
	summ1->left = E;
	summ1->right = F;
	tnode *prod1 = malloc(sizeof(tnode));
	prod1->data = malloc(sizeof(struct value_t));
	((value_t*)(prod1->data))->operation = prod;
	prod1->left = D;
	prod1->right = summ1;
	tnode *diff2 = malloc(sizeof(tnode));
	diff2->data = malloc(sizeof(struct value_t));
	((value_t*)(diff2->data))->operation = diff;
	diff2->left = prod1;
	diff2->right = diff1;
	tnode *summ2 = malloc(sizeof(tnode));
	summ2->data = malloc(sizeof(struct value_t));
	((value_t*)(summ2->data))->operation = summ;
	summ2->left = C;
	summ2->right = diff2;	
	tnode *summ3 = malloc(sizeof(tnode));
	summ3->data = malloc(sizeof(struct value_t));
	((value_t*)(summ3->data))->operation = summ;
	summ3->left = summ2;
	summ3->right = I;	
	tnode *prod2 = malloc(sizeof(tnode));
	prod2->data = malloc(sizeof(struct value_t));
	((value_t*)(prod2->data))->operation = prod;
	prod2->left = B;
	prod2->right = summ3;

	tnode *root = malloc(sizeof(tnode));
	root->data = malloc(sizeof(struct value_t));
	((value_t*)(root->data))->operation = summ;
	root->left = A;
	root->right = prod2;
	return root;
}

void free_tree(tnode* n)\
{
	traverse_postfix(n, free);
}

void print_tree(tnode* n, int level, method_t printer)
{
	if (n != NULL)
	{
		if (n->left)
			print_tree(n->left, level + 1, printer);
		for (int i = 0; i < level; i++)
			printf("        ");
		printer(n);
		if (n->right)
			print_tree(n->right, level + 1, printer);
	}
	else if (level == 0)
		printf("Tree is empty\n");
}

void traverse_postfix(tnode* root, method_t action)
{
	if (root == NULL)
		return;
	traverse_postfix(root->left, action);
	traverse_postfix(root->right, action);
	action(root);
}

void traverse_infix(tnode* root, method_t action)
{
	if (root == NULL)
		return;
	traverse_infix(root->left, action);
	action(root);	
	traverse_infix(root->right, action);
}

void traverse_prefix(tnode* root, method_t action)
{
	if (root == NULL)
		return;
	action(root);
	traverse_prefix(root->left, action);
	traverse_prefix(root->right, action);
}

int compare_keys(tnode *k, tnode *x)
{
	if (k != NULL && x != NULL)
	{
		float k_res = *(float*)k->key;
		float x_res = *(float*)x->key;
		if (k_res > x_res)
			return 1;
		if (k_res == x_res)
			return 0;
		return -1;
	}
	if (k != NULL)
		return 1;
	return -1;
}

tnode* tree_add(tnode* root, tnode* node)
{
	if (root == NULL)
	{
		return node;
	}

	int cmp = compare_keys(root, node);
	if (cmp < 0)
	{
		if (root->left == NULL)
			root->left = node;
		else
			tree_add(root->left, node);
	}
	if (cmp > 0)
	{
		if (root->right == NULL)
			root->right = node;
		else
			tree_add(root->right, node);
	}
	if (cmp == 0)
	{
		free(root->data);
		root->data = node->data;
	}
	return root;
}


tnode *get(tnode *tree, float k)
{
	tnode *x = tree;
	while (x != NULL)
	{
		int cmp = *(float*)x->key - k;
		if (cmp == 0)
			return x;
		if (cmp < 0)
			x = x->left;
		else
			x = x->right;
	}
	return NULL;
}

tnode *get_parent(tnode *tree, float k, int *side)
{
	tnode *x = tree;
	tnode *p = tree;
	while (x != NULL)
	{
		printf("Key: %d, node: %d\n", k, x->key);
		int cmp = k - *(float*)x->key;
		if (cmp == 0)
		{
			if (p == x)
				return NULL;			
			return p;
		}
		p = x;
		if (cmp < 0)
		{
			x = x->left;
			*side = -1;
		}
		else
		{
			x = x->right;
			*side = 1;
		}
		
	}
	return NULL;
}


void tree_remove(tnode** root, float k, tnode** removed)
{
	tnode* x = *root;
	tnode *y = NULL;
	while (x != NULL)
	{
		int cmp = *(float*)x->key -k;
		printf("%d\n", cmp);
		if (cmp == 0) {
			break;
		}
		y = x;
		if (cmp < 0) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	if (x == NULL)
	{
		printf("Key not foun!\n");
		return;
	}
	if (x->right == NULL) {
		if (y == NULL) {
			*root = x->left;
		}
		else {
			if (x == y->left) {
				y->left = x->left;
			}
			else {
				y->right = x->left;
			}
		}
	}
	else {
		tnode* leftMost = x->right;
		y = NULL;
		while (leftMost->left != NULL) {
			y = leftMost;
			leftMost = leftMost->left;
		}
		if (y != NULL) {
			y->left = leftMost->right;
		}
		else {
			x->right = leftMost->right;
		}
		x->key = leftMost->key;
		x->data = leftMost->data;
	}
}

void dkey_printer(tnode *n)
{
	printf("%d ", n->key);
}

void tsort(int* arr, ulong length)
{
	tnode *tree = NULL;
	for (ulong i = 0; i < length; i++)
	{
		tnode *node = malloc(sizeof(tnode));
		node->key = arr[i];
		node->left = NULL;
		node->right = NULL;
		node->data = NULL;
		tree = tree_add(tree, node);
	}
	traverse_infix(tree, dkey_printer);
	printf("\n");
}

// AVL
unsigned char height(tnode *p)
{
	return p ? p->height : 0;
}
int bfactor(tnode *p)
{
	return height(p->right) - height(p->left);
}

void fixheight(tnode *p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	if (hl > hr)
		p->height = hl + 1;
	else
		p->height = hr + 1;
}

tnode *rot_r(tnode* p)
{
	tnode *q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

tnode *rot_l(tnode* q)
{
	tnode *p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

tnode *balance(tnode *p)
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rot_r(p->right);
		return rot_l(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rot_l(p->left);
		return rot_r(p);
	}
	return p;
}

tnode* avl_add(tnode* root, tnode* node)
{
	if (!root)
		return node;
	if (*(float*)node->key > *(float*)root->key)
		root->left = avl_add(root->left, node);
	else
		root->right = avl_add(root->right, node);
	return balance(root);
}

tnode* get_cnt(tnode* tree, float k, int *comparisons)
{
	tnode *x = tree;
	*comparisons = 0;
	while (x != NULL)
	{
		(*comparisons)++;
		int cmp = *(float*)x->key - k;
		if (cmp == 0)
			return x;
		if (cmp < 0)
			x = x->left;
		else
			x = x->right;
	}
	return NULL;
}
