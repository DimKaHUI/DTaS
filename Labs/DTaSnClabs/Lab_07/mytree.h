#pragma once

typedef unsigned long long ulong;

enum operation_type                // ��� ��������
{
	summ, prod, diff, none
};

typedef struct value_t             // ������, ������� ������ ���� ������
{
	enum operation_type operation;
	float result;
}value_t;

typedef struct tnode               // ���� ������
{	
	unsigned char height;
	void *key;
	void *data;
	struct tnode *left;
	struct tnode *right;	
} tnode;

typedef void(*method_t)(tnode*);
typedef int(*comparator)(tnode*);

// ���������� ��������� ��� ������
tnode *build_expr(float a, float b, float c, float d, float e, float f, float g, float h, float i);

void free_tree(tnode *n);                                    // ������������ ������, ���������� ��� ������
void print_tree(tnode *n, int level, method_t printer);      // ������ ������, ������� ������ �������� ��������

void traverse_postfix(tnode *root, method_t action);         // ���� ������� �����
void traverse_infix(tnode *root, method_t action);           // ��������� �����
void traverse_prefix(tnode *root, method_t action);          // ���������� �����
float calculate(tnode* root);                                // ���������� ���������

tnode *tree_add(tnode *root, tnode *node);                   // ���������� ���� � ������
void tree_remove(tnode** root, int k, tnode** removed);      // �������� ���� �� ������
tnode *get(tnode *tree, float k);                            // ����� ���� �� �����
tnode *get_val(tnode *tree, void* value);                    // ����� ���� �� ��������

// ��� ��� ��������
tnode *avl_add(tnode *root, tnode *node);                   // ���������� ���� � ������

tnode *get_cnt(tnode *tree, float k, int *comparisons);      // ����� ���� �� �����