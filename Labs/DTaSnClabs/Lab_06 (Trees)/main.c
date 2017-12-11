#define _CRT_SECURE_NO_WARNINGS

#include "mytree.h"
#include <stdio.h>
#include <math.h>

#define EPS 0.001
#define ERROR_ILLEGAL_SYMBOL -111

float calculate(tnode *n)
{
	switch (n->data->operation)
	{
	case summ:
		return calculate(n->left) + calculate(n->right);
	case prod:
		return calculate(n->left) * calculate(n->right);
	case diff:
		return  calculate(n->left) - calculate(n->right);
	default:
		return n->data->result;
	}
}

int main(void)
{	
	printf("1. Calculate expression\n");

	int cmd = -1;
	int err = 0;
	do
	{
		if (scanf("%d", &cmd) != 1)
		{
			err = ERROR_ILLEGAL_SYMBOL;
		}
		else
		{			
			float a, b, c, d, e, f, g, h, i;
			printf("Input values for A, B, ... , I\n");
			if (scanf("%f %f %f %f %f %f %f %f %f", &a, &b, &c, &d, &e, &f, &g, &h, &i) != 9)
			{
				err = ERROR_ILLEGAL_SYMBOL;
			}
			else
			{
				tnode *expr = build_expr(a, b, c, d, e, f, g, h, i);
				float res = calculate(expr);
				printf("Result of calculation: %3.2f\n", res);
				float check = a + (b * (c + (d * (e + f) - (g - h)) + i));
				if (fabs(res - check) <= EPS)
					printf("Result is correct!\n");
				else
					printf("Correct result: %3.2f\n", check);
			}
		}
	} while (cmd != 0);
}
