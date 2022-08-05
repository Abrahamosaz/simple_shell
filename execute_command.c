#include "shell.h"
/**
 * execute_command - execute the command line arguments
 * @argv: command line arguments
 *
 * Return: return -1
 */
int execute_command(char **argv)
{
	pid_t childid;
	size_t j, k, i = 0;
	char **buffer;

	if (!argv)
		return (-1);
	while (argv[i])
		i++;
	buffer = malloc(sizeof(char *) * i - 1);
	if (buffer == NULL)
		return (-1);
	for (j = 0, k = j + 1; j < i; j++, k++)
		buffer[j] = argv[k];
	buffer[j] = NULL;
	childid = fork();
	if (childid == -1)
	{
		perror(argv[0]);
		return (-1);
	}
	if (childid == 0)
	{
		if (execve(buffer[0], buffer, environ) == -1)
		{
			perror(argv[0]);
			exit(-1);
		}
	}
	waitpid(childid, NULL, 0);
	free(buffer);
	return (-1);
}
