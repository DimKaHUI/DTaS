#pragma once
#include "matrix.h"

#define ERROR_IO -111
#define ERROR_SIZES -112

int read_graph(matrix *m);
float longest_way(matrix *W0);