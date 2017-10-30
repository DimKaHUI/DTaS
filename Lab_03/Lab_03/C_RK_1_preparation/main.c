#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include  <conio.h>
#include <ctype.h>

#define BSIZE 16

void make_std(char *line);
void sort_alph(char *line);
void sort_len(char *line);

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		return -1;
	}

	FILE *f = fopen(argv[1], "r");
	if (f == NULL)
	{
		printf("No file\n");
		return -1;
	}

	char *line = NULL; // source line
	// Reading source line
	int length = 0;
	char buff[BSIZE];
	int nuller_pos = 0;
	while (fgets(buff, BSIZE, f))
	{
		int shift = length;
		if (length == 0)
		{
			line = malloc(BSIZE - 1);
		}
		else
		{
			line = realloc(line, length + BSIZE - 1);
		}

		length += BSIZE - 1;
		int i = 0;
		while (buff[i] != '\0')
		{
			line[shift + i] = buff[i];
			i++;
		}
		if (buff[i] == '\0')
			nuller_pos = shift + i;
	}
	line = realloc(line, nuller_pos);
	line[nuller_pos] = '\0';

	// Checking line
	printf("Line: %s\n", line);

	// Making line standard
	make_std(line);
	printf("Std: *%s*\n", line);

	sort_alph(line);
	//sort_len(line);

	_getch();
	return 0;
}

void make_std(char *line)
{
	// Make first letter upper
	line[0] = toupper(line[0]);

	// Removing spaces
	int pos = 0;
	while (line[pos] != '\0')
	{
		if (line[pos] != ' ')
		{
			pos++;
			continue;
		}

		if (line[pos - 1] != ' ')
		{
			pos++;
			continue;
		}

		int i = pos - 1;
		while (line[i] != '\0')
		{
			line[i] = line[i + 1];
			i++;
		}
	}

	// Removing spaces before signs
	pos = 0;
	while (line[pos] != '\0')
	{
		if (
			line[pos] != '.' &&
			line[pos] != ',' &&
			line[pos] != '!' &&
			line[pos] != '?' &&
			line[pos] != ';'
			)
		{
			pos++;
			continue;
		}

		if (line[pos - 1] != ' ')
		{
			pos++;
			continue;
		}

		int i = pos - 1;
		while (line[i] != '\0')
		{
			line[i] = line[i + 1];
			i++;
		}
	}

	// Adding space after sign
	pos = 0;
	while (line[pos] != '\0')
	{
		if (
			line[pos] != '.' &&
			line[pos] != ',' &&
			line[pos] != '!' &&
			line[pos] != '?' &&
			line[pos] != ';'
			)
		{
			pos++;
			continue;
		}

		if (line[pos + 1] == ' ')
		{
			pos++;
			continue;
		}

		int i = 0;
		while (line[i] != '\0')
		{
			i++;
		}

		while (i > pos)
		{
			line[i] = line[i - 1];
			i--;
		}
		line[pos + 1] = ' ';
		pos++;
	}

	// Replacing last char with dot
	int len = 0;
	while (line[len] != '\0')
		len++;
	if (line[len - 1] == ' ')
		line[len - 1] = '.';
	else
	{

		line[len + 1] = '\0';
		line[len] = '.';
	}
}

void sort_alph(char* line)
{
	// Removing signs
	int i = 0;
	while (line[i] != '\0')
	{
		if (
			line[i] != '.' &&
			line[i] != ',' &&
			line[i] != '!' &&
			line[i] != '?' &&
			line[i] != ';'
			)
		{
			i++;
			continue;
		}

		int pos = i;
		while (line[pos] != '\0')
		{
			line[pos] = line[pos + 1];
			pos++;
		}
	}

	printf("No signs: %s\n", line);

	char **words;
	// Counting words
	i = 0;
	int words_cnt = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			words_cnt++;
		i++;
	}
	words_cnt++;
	printf("Words count: %d\n", words_cnt);
	words = (char**)malloc(sizeof(char*) * words_cnt);

	for (int j = 0; j < words_cnt; j++)
	{
		words[j] = NULL;
	}

	printf("Alllocation completed!\n");

	i = 0;
	int word_num = 0;
	while (line[i] != '\0')
	{

		word_num++;
		i++;

		// Counting length
		int k = i;
		while (line[k] != '\0' && line[k] != ' ')
			k++;

		printf("K - i + 1 = %d\n", k - i + 1);
		words[word_num] = malloc(k - i + 1);
		for (k = i; line[k] != ' ' && line[k] != ' '; k++)
		{
			words[word_num][k - i] = line[k];
		}
		words[k] = '\0';
	}

	// Printing words
	for (int j = 0; j < words_cnt; j++)
	{
		printf("%s\n", words[j]);
	}
}
