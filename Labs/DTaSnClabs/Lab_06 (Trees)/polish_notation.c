#include <stdlib.h>
#include "polish_notation.h"
#include "dinarrstack.h"
#include <stdio.h>

punit *build_expr_polish(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	punit *expr = malloc(sizeof(punit) * 17);
	expr[0].operation = none;
	expr[0].value = e;
	expr[1].operation = none;
	expr[1].value = f;
	expr[2].operation = summ;
	expr[2].value = 0;
	expr[3].operation = none;
	expr[3].value = d;
	expr[4].operation = prod;
	expr[4].value = 0;
	expr[5].operation = none;
	expr[5].value = g;
	expr[6].operation = none;
	expr[6].value = h;
	expr[7].operation = diff;
	expr[7].value = 0;
	expr[8].operation = diff;
	expr[8].value = 0;
	expr[9].operation = none;
	expr[9].value = c;
	expr[10].operation = summ;
	expr[10].value = 0;
	expr[11].operation = none;
	expr[11].value = i;
	expr[12].operation = summ;
	expr[12].value = 0;
	expr[13].operation = none;
	expr[13].value = b;
	expr[14].operation = prod;
	expr[14].value = 0;
	expr[15].operation = none;
	expr[15].value = a;
	expr[16].operation = summ;
	expr[16].value = 0;
	return expr;
}

float polish_calculate(punit* expression, int len)
{
	DinArrStack stack;
	dinarr_create(&stack);
	for (int i = 0; i < len; i++)
	{
		float left, right;
		switch (expression[i].operation)
		{
		case summ: 
			//printf("Summing!\n");
			dinarr_remove(&stack, &right);
			dinarr_remove(&stack, &left);
			//printf("Left: %3.2f, Right: %3.2f, Result: %3.2f\n", left, right, left + right);
			dinarr_add(&stack, left + right);
			break;
		case prod:
			//printf("Producting!\n");
			dinarr_remove(&stack, &right);
			dinarr_remove(&stack, &left);
			//printf("Left: %3.2f, Right: %3.2f, Result: %3.2f\n", left * right);
			dinarr_add(&stack, left * right);
			break;
		case diff: 
			//printf("Differing!\n");
			dinarr_remove(&stack, &right);
			dinarr_remove(&stack, &left);
			//printf("Left: %3.2f, Right: %3.2f, Result: %3.2f\n", left, right, left - right);
			dinarr_add(&stack, left - right);
			break;
		case none:
			//printf("Memorizing %3.2f!\n", expression[i].value);
			dinarr_add(&stack, expression[i].value);
			break;
		default:;
		}
	}
	float res;
	dinarr_remove(&stack, &res);
	return res;
}
