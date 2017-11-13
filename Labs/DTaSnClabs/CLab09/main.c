#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "mystring.h"

int main(int argc, char **argv)
{
	if (argc < 4)
	{
		printf("Use cmd argument <input><output><substring source><substring replace with>\n");
		return -1;
	}

	FILE *in = fopen(argv[1], "r");
	if (in == NULL)
	{
		printf("Input file does not exist\n");
		return -1;
	}
	FILE *out = fopen(argv[2], "w");
	if (out == NULL)
	{
		printf("Impossible to create or rewrite output file\n");
		return -1;
	}

	printf("Mask %s replacing with %s\n\n", argv[3], argv[4]);

	int len = 0;
	while (!feof(in))
	{
		char *line;
		len = my_getdelim(&line, NULL, (int)'\n', in);
		printf("%d : %s \n", len, line);
		char *nline = str_replace(line, "Putin", "Trump");
		fprintf(out, "%s\n", nline);
		free(line);
		free(nline);
	}

	return 0;
}
