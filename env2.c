#include "shell.h"
/**
 * search_path - search for a particuler path that matches the command
 * @args: argument enter by the user
 * @argv: first argument of the shell
 *
 * Return: return pointer
 */
char *search_path(char **args, char *argv)
{
	struct path_env *trans;
	char slash[1] = "/", *path = NULL;
	int len;

	if (check_file(args[0]) == 0)
		return ("find");
	trans = set_path();
	while (trans)
	{
		len = _strlen(trans->string) + 1 + _strlen(args[0]);
		path = malloc(sizeof(char) * len);
		if (!path)
			return (NULL);
		_strcat(path, trans->string);
		_strcat(path, slash);
		_strcat(path, args[0]);
		if (check_file(path) == 0)
		{
			free_list(trans);
			return (path);
		}
		free(path);
		path = NULL;
		trans = trans->next;
	}
	free_list(trans);
	perror(argv);
	return (NULL);
}
/**
 *
 *
 *
 */
ssize_t unsetenv_shell(char *name)
{
	unsigned int i = 0;

	if (!name)
		return (1);
	while (environ[i])
	{
		if (_strncmp(environ[i], name, _strlen(name)) ==  0)
		{
			free(environ[i]);
			return (1);
		}
		i++;
	}
	return (1);
}
/**
 * _cd - changes directory
 * @token: command
 * @value: directory name
 * @extra: third user input argument
 * Return: 1
 */
ssize_t _cd(char *token, char *value, char *extra)
{
	char *current_dir, *dir;

	current_dir = _getenv("PWD");
	dir = malloc(sizeof(char) * 1024);
	if (extra)
	{
		perror("too many arguments");
		return (1);
	}
	if (token && !value && !extra)
		chdir(_getenv("HOME"));
	if (value)
		shorten(value);
	setenv_shell(token, "OLDPWD", current_dir);
	setenv_shell(token, "PWD", getcwd(dir, 1024));
	free(dir);
	return (1);
}
/**
 * shorten - changes directory when directory is specified
 * @value: name of directory
 * Return: void
 */
void shorten(char *value)
{
	char *current_dir, *new_dir, *slash, *home_dir, *target_dir;

	current_dir = _getenv("PWD");
	home_dir = malloc(sizeof(char) * 100);
	target_dir = malloc(sizeof(char) * 1024);
	slash = malloc(sizeof(char) * (strlen(value) + 1));
	strcat((_strcpy(home_dir, _getenv("HOME"))), "/");

	if ((value[0] == '-' && value[1] == '-') && !(value[2]))
		new_dir = home_dir;
	else if (value[0] == '-' && !(value[1]))
		new_dir = _getenv("OLDPWD");
	else if (value[0] == '~' && !(value[1]))
		new_dir = home_dir;
	else
	{
		_strcat(_strcpy(slash, "/"), value);
		_strcat((strcpy(target_dir, current_dir)), slash);
	}
	if (new_dir == home_dir)
		chdir(home_dir);
	else if (new_dir == _getenv("OLDPWD"))
	{
		printf("%s\n", _getenv("OLDPWD"));
		chdir(_getenv("OLDPWD"));
	}
	else if (access(target_dir, F_OK) == 0)
		chdir(target_dir);
	else if (!value)
		chdir(home_dir);
	else
		perror("Directory does not exist");
	free(home_dir);
	free(target_dir);
	free(slash);
}
