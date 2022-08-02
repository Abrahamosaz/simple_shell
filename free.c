#include "shell.h"
/**
 * free_str - frees allocated memory of all string literals in argv
 * @argv: array of pointers
 * Return: void
 */
void free_str(char **argv)
{
	size_t count = 0, i;

	while (argv[count])
		count++;
	for (i = 0; i < count; i++)
	{
		free(argv[i]);
	}
	free(argv);
}
