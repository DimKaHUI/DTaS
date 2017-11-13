#ifndef MYSTRING_H
#define MYSTRING_H

#include <stdlib.h>
#include <stdio.h>

// strspn, strndup

size_t my_strspn(const char * str1, const char * str2);
char *my_strndup(const char *str, size_t size);
size_t my_getdelim(char **lineptr, size_t *n, int delimiter, FILE *stream);
char *str_replace(const char* source, const char* serach, const char *replace);
int streq(const char *str1, const char *str2);
char *str_replace(const char *source, const char *search, const char *replace);

#endif // MYSTRING_H
