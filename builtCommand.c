#include "shell.h"
#define ERROR_MESSAGE                                      \
write(STDERR_FILENO, "couldn't set variable\n", 23)
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
		{"cd", _cd},
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
	size_t i = 0, check = 0, total_len, x, j, h = 0;
	char *name = args[1], *value = args[2], *buffer = NULL, *store = NULL;

	if (!name || !value)
	{
		ERROR_MESSAGE;
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
		_setenv(args, &check, store);
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
/**
 * _cd - changes directory
 * @tokens: array of pointers to user input
 * Return: 0
 */
ssize_t _cd(char **tokens)
{
	char *current_dir, *new_dir, *slash, *home_dir, *dir, *target_dir;

	if (tokens[2])
	{
		perror("too many arguments");
		return (1);
	}
	if (tokens[1])
	{
		home_dir = malloc(sizeof(char) * 100);
		dir = malloc(sizeof(char) * 1024);
		target_dir = malloc(sizeof(char) * 1024);
		slash = malloc(sizeof(char) * (strlen(tokens[1]) + 1));
		current_dir = _getenv("PWD");

		strcat((_strcpy(home_dir, _getenv("HOME"))), "/");
		if ((tokens[1][0] == '-' && tokens[1][1] == '-') && !(tokens[1][2]))
			new_dir = home_dir;
		else if (tokens[1][0] == '-' && !(tokens[1][1]))
			new_dir = _getenv("OLDPWD");
		else if (tokens[1][0] == '~' && !(tokens[1][1]))
			new_dir = home_dir;
		else
		{
			_strcat(_strcpy(slash, "/"), tokens[1]);
			_strcat((strcpy(target_dir, current_dir)), slash);
		}
	} else if (tokens[1] == "cd")
		new_dir = home_dir;
	if (new_dir == home_dir)
		chdir(home_dir);
	else if (new_dir == _getenv("OLDPWD"))
	{
		chdir(_getenv("OLDPWD"));
		printf("%s\n", _getenv("OLDPWD"));
	} else if (access(target_dir, F_OK) == 0)
	{
		chdir(target_dir);
	} else
		perror("Directory does not exist");
	setenv("OLDPWD", current_dir, 1);
	setenv("PWD", getcwd(dir, 1024), 1);
	free(home_dir);
	free(dir);
	free(target_dir);
	free(slash);
	return (1);
}
