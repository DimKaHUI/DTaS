#include <stdlib.h>
#include <stdio.h>

#define BSIZE 32

int streq(const char *str1, const char *str2)
{
	int i;
	for (i = 0; str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i]; i++);
	return str1[i] == str2[i];
}

size_t my_strspn(const char *str1, const char *str2)
{
	int len = 0;
	for (int i = 0; str1[i] != '\0'; i++)
	{
		int k;
		for (k = 0; str2[k] != '\0' && str2[k] != str1[i]; k++);
		if (str2[k] != '\0')
			len++;
		else if (len != 0)
			return len;
		else if (i == 0)
			return 0;
	}
	return 0;
}

char *my_strndup(const char *str, size_t size)
{
	int len;
	for (len = 0; str[len] != '\0' && len < size; len++);

	char *result = malloc(len + 1);
	for (int i = 0; i < len; i++)
	{
		result[i] = str[i];
	}
	result[len] = '\0';
	return result;
}

size_t my_getdelim(char **lineptr, size_t *n, int delimiter, FILE *stream)
{
	*lineptr = NULL;
	char *line = NULL;
	char buff[BSIZE];
	int del_reached = 0;
	int line_len = 0;

	int file_position = ftell(stream);

	while (fgets(buff, BSIZE, stream) && !del_reached)
	{
		// Finding delimeter
		int buff_len;
		for (buff_len = 0; buff[buff_len] != '\0' && buff[buff_len] != (char)delimiter && buff_len < BSIZE; buff_len++);

		if (buff[buff_len] == (char)delimiter)
			del_reached = 1;

		file_position += buff_len + 1;
		fseek(stream, file_position, 0);

		// Allocating memory
		if (line == NULL)
		{
			line = malloc((buff_len + 1) * sizeof(char));
		}
		else
		{
			line = realloc(line, (line_len + buff_len + 1) * sizeof(char));
		}

		if (line == NULL)
			return 0;

		// Appending
		for (int i = line_len; i < line_len + buff_len; i++)
		{
			line[i] = buff[i - line_len];
		}


		line_len += buff_len;
	}

	line[line_len] = '\0';
	//printf("Delimiter reached: %d\n", del_reached);
	*lineptr = line;
	return line_len;
}

char *str_replace(const char *source, const char *search, const char *replace)
{
	int srclen, searchlen, replen;
	for (srclen = 1; source[srclen - 1] != '\0'; srclen++);
	for (searchlen = 1; search[searchlen - 1] != '\0'; searchlen++);
	for (replen = 1; replace[replen - 1] != '\0'; replen++);
	int shift = replen - searchlen; // If shift > 0 then we need to shift rightwards, else leftwards
	//printf("Shift: %d\n", shift);

	if (srclen <= 0)
		return NULL;

	char *result = malloc(srclen);
	for (int i = 0; i == 0 || source[i - 1] != '\0'; i++)
	{
		result[i] = source[i];
	}

	for (int i = 0; result[i + searchlen - 2] != '\0'; i++)
	{
		/*printf("----------------------\n");
		for(int k = 0; k < i; k++)
		printf(" ");
		printf("*\n");
		printf("%s\n", result);*/

		int mask = 0;
		for (; result[i + mask] == search[mask] && search[mask] != '\0' && result[i + mask] != '\0'; mask++);

		/*if(mask > 3)
		printf("Mask: %d, slen: %d\n", mask, searchlen);*/
		if (mask + 1 != searchlen)
			continue;

		if (shift < 0)
		{
			// Shifting leftwards
			for (int k = 0; k < -shift; k++)
			for (int j = i; result[j] != '\0'; j++)
			{
				result[j] = result[j + 1];
				//srclen++;
			}

			for (int k = i; k < i + replen - 1; k++) // replacing existing chars
			{
				result[k] = replace[k - i];
			}

			srclen += shift;
			result = realloc(result, srclen);
			if (result == NULL)
				return NULL;
		}
		else if (shift > 0)
		{
			srclen += shift;
			result = realloc(result, srclen);
			if (result == NULL)
				return NULL;
			// Shifting rightwards
			for (int k = 0; k < shift; k++)
			for (int j = srclen; j > i; j--)
			{
				result[j] = result[j - 1];
				//srclen++;
			}

			for (int k = i; k < i + replen - 1; k++) // replacing existing chars
			{
				result[k] = replace[k - i];
			}
		}
		else
		{
			for (int k = i; k < i + replen - 1; k++) // replacing existing chars
			{
				result[k] = replace[k - i];
			}
		}
		i += replen - 1;
		/*for(int k = 0; k < i; k++)
		printf(" ");
		printf("*\n");
		printf("%s\n", result);*/
	}

	//printf("Returned\n");
	return result;
}
