#ifndef __MYSNPRINTF
#define __MYSNPRINTF

#include <stdlib.h>

/**
 * \brief 
 * \param s Initialized buffer, data will be written inside this
 * \param n Number of chars to be written
 * \param format Format string
 * \param ... Data
 * \return Count of written chars (excluding \0)
 */
int my_snprintf(char * s, size_t n, const char * format, ...);

int strlen(char *str);

int streq(char *str1, char *str2);
#endif