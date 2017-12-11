#include "mytree.h"
#include <stdlib.h>

tnode *build_expr(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	tnode *A = malloc(sizeof(tnode));
	A->data = malloc(sizeof(struct value_t));
	A->data->result = a;
	A->data->operation = none;
	tnode *B = malloc(sizeof(tnode));
	B->data = malloc(sizeof(struct value_t));
	B->data->result = b;
	B->data->operation = none;
	tnode *C = malloc(sizeof(tnode));
	C->data = malloc(sizeof(struct value_t));
	C->data->result = c;
	C->data->operation = none;
	tnode *D = malloc(sizeof(tnode));
	D->data = malloc(sizeof(struct value_t));
	D->data->result = d;
	D->data->operation = none;
	tnode *E = malloc(sizeof(tnode));
	E->data = malloc(sizeof(struct value_t));
	E->data->result = e;
	E->data->operation = none;
	tnode *F = malloc(sizeof(tnode));
	F->data = malloc(sizeof(struct value_t));
	F->data->result = f;
	F->data->operation = none;
	tnode *G = malloc(sizeof(tnode));
	G->data = malloc(sizeof(struct value_t));
	G->data->result = g;
	G->data->operation = none;
	tnode *H = malloc(sizeof(tnode));
	H->data = malloc(sizeof(struct value_t));
	H->data->result = h;
	H->data->operation = none;
	tnode *I = malloc(sizeof(tnode));
	I->data = malloc(sizeof(struct value_t));
	I->data->result = i;
	I->data->operation = none;
	
	tnode *diff1 = malloc(sizeof(tnode));
	diff1->data = malloc(sizeof(struct value_t));
	diff1->data->operation = diff;
	diff1->left = G;
	diff1->right = H;
	tnode *summ1 = malloc(sizeof(tnode));
	summ1->data = malloc(sizeof(struct value_t));
	summ1->data->operation = summ;
	summ1->left = E;
	summ1->right = F;
	tnode *prod1 = malloc(sizeof(tnode));
	summ1->data = malloc(sizeof(struct value_t));
	summ1->data->operation = prod;
	summ1->left = D;
	summ1->right = summ1;
	tnode *diff2 = malloc(sizeof(tnode));
	diff2->data = malloc(sizeof(struct value_t));
	diff2->data->operation = diff;
	diff2->left = prod1;
	diff2->right = diff1;
	tnode *summ2 = malloc(sizeof(tnode));
	summ2->data = malloc(sizeof(struct value_t));
	summ2->data->operation = summ;
	summ2->left = C;
	summ2->right = diff2;
	tnode *prod2 = malloc(sizeof(tnode));
	prod2->data = malloc(sizeof(struct value_t));
	prod2->data->operation = prod;
	prod2->left = B;
	prod2->right = summ2;
	tnode *summ3 = malloc(sizeof(tnode));
	summ3->data = malloc(sizeof(struct value_t));
	summ3->data->operation = prod;
	summ3->left = I;
	summ3->right = prod2;	
	tnode *root = malloc(sizeof(tnode));
	root->data = malloc(sizeof(struct value_t));
	root->data->operation = summ;
	summ3->left = A;
	summ3->right = summ3;

	return root;
}

void free_tree(tnode* n)
{
	traverse_postfix(n, free);
}

void traverse_postfix(tnode* root, method_t action)
{
	if (root == NULL)
		return;
	traverse_infix(root->left, action);	
	traverse_infix(root->right, action);
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

void *search(const tnode root, void *key)
{
	
}
