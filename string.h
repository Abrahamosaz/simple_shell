#ifndef STRING_H
#define STRING_H
/* header files */
#include "shell.h"

/* function declaration */
int _strncmp(char *dest, char *src, size_t n);
char **strtoken(char *buffer);
size_t _strlen(char *str);
int _strword(char *str, char *delim);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
void print_str(char *args);
ssize_t _isalpha(char str);
int _atoi(char *str);
#endif
