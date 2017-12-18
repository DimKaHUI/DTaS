#include <stdio.h>
#include "matrix.h"
#include "graph.h"
#include <conio.h>

int main()
{
	matrix graph;
	int err = read_graph(&graph);
	if (err != 0)
		goto error_handle;
	print_matrix(&graph);
	_getch();

error_handle:
	switch (err)
	{
	case ERROR_IO:
		printf("IO error occured!\n");
		break;
	case ERROR_SIZES:
		printf("Illegal size value!\n");
		break;
	default: ;
	}
}
