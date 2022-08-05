#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *_strtok(char *str, char delim)
{
	static char *buffer = NULL;

	if (buffer == NULL)
		buffer = str;
	if (!*buffer)
		return (NULL);

	char *token = buffer;
	while (*buffer && *buffer != delim)
	{
		buffer++;
	}
	if (*buffer)
	{	
		*buffer = '\0';
		buffer++;
	}
	return (token);
}
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
