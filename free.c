#include "shell.h"
/**
 *
 *
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
