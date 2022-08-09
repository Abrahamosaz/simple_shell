#include "shell.h"
/**
 * built_commands - for commands executed on the shell
 * @argv: arguments passed by the user
 * @first_arg: name of the shell executable file
 *
 * Return: return integer value
 */
ssize_t built_commands(char **argv, char *first_arg)
{
	size_t  i = 0;
	ssize_t exit_status = 0;
	built_in var[] = {
		{"exit", exit_shell},
		{"env", env_shell},
		{"setenv", setenv_shell},
		{"unsetenv", unsetenv_shell},
		{"cd", _cd},
		{NULL, NULL}
	};

	while (var[i]._command)
	{
		if (_strncmp(var[i]._command, argv[0], 0) == 0)
			exit_status = var[i].ptr(argv[0], argv[1], argv[2], argv, first_arg);
		i++;
	}
	return (exit_status);
}
/**
 * exit_shell - To exit the current shell
 * @args: argument passed by the user
 * @t: first argument
 * @t1: second argument
 * @t2: third argument
 * @fst: name of the executable file
 *
 * Return: return integer value
 */
ssize_t exit_shell(char *t, char *t1, char *t2, char **args, char *fst)
{
	ssize_t i = 0, status;

	(void)t;
	(void)t1;
	(void)t2;
	if (!args[1])
		return (-1);
	while (args[1][i])
	{
		if (_isalpha(args[1][i]) == -1)
		{
			write(STDERR_FILENO, fst, _strlen(fst));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, args[0], _strlen(args[0]));
			write(STDERR_FILENO, ": Illegal number: ", 19);
			write(STDERR_FILENO, args[1], _strlen(args[1]));
			write(STDERR_FILENO, "\n", 2);
			return (1);
		}
		i++;
	}
	status = atoi(args[1]);
	free_str(args);
	exit(status);
}
/**
 * env_shell - print out the environ variables
 *
 * Return: return integer value
 */
ssize_t env_shell(void)
{
	unsigned int i = 0;

	while (environ[i])
	{
		print_str(environ[i]);
		i++;
	}
	return (1);
}
/**
 * setenv_shell - set new enviorn variable
 * @tk: first argument
 * @name: name of the varaible
 * @value: value of the varaible
 * @f: arryays of pinters of the arguments
 * @fst: name of the shell executable
 *
 * Return: return integer value 1
 */
ssize_t setenv_shell(char *tk, char *name, char *value, char **f, char *fst)
{
	size_t i = 0, check = 0, x, j, h = 0;
	char *buffer = NULL, *store = NULL;

	if (!name || !value)
	{
		set_error(tk, fst);
		return (1);
	}
	buffer = malloc(sizeof(char) * _strlen(name) + _strlen(value) + 1);
	if (buffer == NULL)
	{
		free(buffer);
		return (1);
	}
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
		_setenv(name, value, &check, store);
		return (1);
	}
	for (j = 0; j < _strlen(name); j++)
		buffer[j] = name[j];
	buffer[j] = '=';
	for (x = 0, j += 1; x < _strlen(value); x++, j++)
		buffer[j] = value[x];
	buffer[j] = '\0';
	while (environ[h])
		h++;
	environ[h] = buffer;
	environ[h + 1] = NULL;
	return (1);
}
/**
 * _setenv - set environ variable of exiting varaibles
 * @name: name of the variable
 * @value: value of change to
 * @n: check value
 * @address: address of the variable
 *
 * Return: return void
 */
void _setenv(char *name, char *value, size_t *n, char *address)
{
	ssize_t i = 0, j = 0;
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
