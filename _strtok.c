#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * _strtok - tokenizes string
 * @str: string to be tokenized
 * @delim: breakpoint character
 * Return: string token
 */
char *_strtok(char *str, char delim)
{
	static char *buffer;

	if (buffer == NULL)
		buffer = str;
	if (*buffer == '\0')
		return (NULL);

	char *token = buffer;

	while (*buffer && *buffer != delim)
	{
		if (*buffer != delim)
			buffer++;
		else
			break;
	}
	if (*buffer)
	{
		*buffer = '\0';
		buffer++;
	}
	return (token);
}
/**
 * main - Code entrypoint
 * Return: 0
 */
int main(void)
{
	char str[80] = "This is a test of strtok";
	char delim = ' ', *token = NULL;

	token = _strtok(str, delim);
	while (token)
	{
		printf("%s\n", token);
		token = _strtok(NULL, delim);
	}
	return (0);
}
