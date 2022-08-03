#include "shell.h"
/**
 * built_commands - for commands executed on the shell
 * @argv: arguments passed by the user
 *
 * Return: return integer value
 */
ssize_t built_commands(char **argv)
{
	size_t  i = 0;
	ssize_t exit_status;
	built_in var[] = {
		{"exit", &exit_shell},
		{NULL, NULL}
	};

	while (var[i]._command)
	{
		if (_strncmp(var[i]._command, argv[0], 0) == 0)
			exit_status = var[i].ptr(argv);
		i++;
	}
	return (exit_status);
}
/**
 * exit_shell - To exit the current shell
 * @args: argument passed by the user
 *
 * Return: return integer value
 */
ssize_t exit_shell(char **args)
{
	(void)args;
	return (-1);
}
