#include "shell.h"
/**
 * free_str - free malloc memory allocated
 * @argv: argument stored on the heep by malloc
 *
 * Return: return void
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
