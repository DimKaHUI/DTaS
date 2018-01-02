#include "mysnprintf.h"
#include <stdarg.h>

#define ASCII_SHIFT 48

#define ABS(a) a >= 0 ? a : -a
#define SIGN(a) a >= 0 ? 1 : -1

char *my_litoa(long int i)
{
	char *result;
	if (i == 0)
	{
		result = malloc(2);
		result[0] = '0';
		result[1] = '\0';
		return result;
	}

	int lenght = 0;
	if (i < 0)
		lenght = 1;	
	
	int tmp = ABS(i);
	int sign = SIGN(i);
	i = tmp;
	while (i > 0)
	{
		lenght++;
		i /= 10;
	}

	result = malloc(lenght + 1);

	if (sign < 0)
		result[0] = '-';

	int pos = lenght - 1;
	while (tmp > 0)
	{
		result[pos] = tmp % 10 + ASCII_SHIFT;
		tmp /= 10;
		pos--;
	}
	result[lenght] = '\0';
	return result;
}

int my_snprintf(char* s, size_t n, const char* format, ...)
{
	if (n == 0)
	{
		s[0] = '\0';
		return -1;
	}

	//n--; // Leaving space for \0

	// Arguments
	va_list vl;
	va_start(vl, format);	

	int pos = 0;
	for (int i = 0; format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			if (pos < n)
				s[pos] = format[i];
			pos++;
			continue;
		}
		if (format[i + 1] == 'l' && format[i + 2] == 'i') // %li
		{
			long int arg = va_arg(vl, long int);
			char *converted = my_litoa(arg);
			for (int j = 0; converted[j] != '\0'; j++, pos++)
			if (pos < n)
				s[pos] = converted[j];
			free(converted);
			i += 2;
		}
		if (format[i + 1] == 'i')                         // %i
		{
			int arg = va_arg(vl, int);
			char *converted = my_litoa(arg);
			for (int j = 0; converted[j] != '\0'; j++, pos++)
			if (pos < n)
				s[pos] = converted[j];
			free(converted);
			i += 1;
		}
		if (format[i + 1] == 's')                         // %s
		{
			char *arg = va_arg(vl, char*);
			for (int j = 0; arg[j] != '\0'; j++, pos++)
			if (pos < n)
				s[pos] = arg[j];
			i += 1;
		}
	}
	s[pos > n ? n : pos] = '\0';
	va_end(vl);
	return pos;
}

int strlen(char* str)
{
	int len = 0;
	for (; str[len] != '\0'; len++);
	return len;
}

int streq(char* str1, char* str2)
{
	int i = 0;
	for (; str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i]; i++);
	return str1[i] == str2[i];
}
