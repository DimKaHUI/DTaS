#pragma once

#include "mytree.h"
#include "dinarrstack.h"

typedef struct polish_unit
{
	enum operation_type operation;
	float value;
}punit;

punit *build_expr_polish(float a, float b, float c, float d, float e, float f, float g, float h, float i);

float polish_calculate(punit *expression, int len);