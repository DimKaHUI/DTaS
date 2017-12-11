#pragma once

enum operation_type
{
	summ, prod, diff, none
};

typedef struct value_t
{
	enum operation_type operation;
	float result;
}value_t;

typedef struct tnode
{	
	value_t *data;
	tnode *left;
	tnode *right;	
} tnode;

typedef void(*method_t)(tnode*);
typedef int(*comparator)(tnode*);

tnode *build_expr(float a, float b, float c, float d, float e, float f, float g, float h, float i);
void free_tree(tnode *n);

void traverse_postfix(tnode *root, method_t action);
void traverse_infix(tnode *root, method_t action);
void traverse_prefix(tnode *root, method_t action);