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
	ssize_t exit_status = 0;
	built_in var[] = {
		{"exit", exit_shell},
		{"env", env_shell},
		{"setenv", setenv_shell},
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
/**
 *
 *
 */
ssize_t env_shell(void)
{
	unsigned int i = 0;
	char **new_environ = environ;

	while (environ[i])
	{
		print_str(environ[i]);
		i++;
	}
	return (1);
}
/**
 *
 *
 *
 */
ssize_t setenv_shell(char **args)
{
	size_t i = 0, check = 0;
	int len1, len2, total_len, x, j;
	char *name = args[1], *value = args[2], *buffer, *store;

	while (environ[i])
	{
		if (_strncmp(environ[i], name, _strlen(name)) == 0)
		{
			check = 1;
			store = environ[i];
			break;
		}
		i++;
	}
	if (check)
	{
		_setenv(args, &check, store);
		return (1);
	}
	len1 = _strlen(name);
	len2 = _strlen(value);
	total_len = len1 + len2;
	buffer = malloc(sizeof(char) * total_len + 1);
	if (buffer == NULL)
		return (-1);
	for (j = 0; j < len1; j++)
		buffer[j] = name[j];
	buffer[j] = '=';
	for (x = 0, j += 1; x < len2; x++, j++)
		buffer[j] = value[x];
	buffer[j] = '\0';
	i = 0;
	while (environ[i])
		i++;
	x = 0;
	environ[i] = buffer;
	environ[i + 1] = NULL;
	return (1);
}
/**
 *
 *
 */
void _setenv(char **args, ssize_t *n, char *address)
{
	ssize_t i = 0, j = 0;
	char *name = args[1], *value = args[2];
	ssize_t len1 = _strlen(name), len2 = _strlen(value);

	if (!n || !address)
		return;
	while (i < len1)
	{
		address[i] = name[i];
		i++;
	}
	address[i] = '=';
	i += 1;
	while (j < len2)
	{
		address[i] = value[j++];
		i++;
	}
	address[i] = '\0';
}
