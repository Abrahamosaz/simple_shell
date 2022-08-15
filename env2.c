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
	struct path_env *trans, *head = NULL;
	char slash[1] = "/", *path = NULL;
	ssize_t len;

	if (check_file(args[0]) == 0)
		return ("find");
	trans = set_path();
	head = trans;
	while (trans)
	{
		len = _strlen(trans->string) + 1 + _strlen(args[0]);
		path = malloc(sizeof(char) * (len + 1));
		if (!path)
		{
			free(path);
			return (NULL);
		}
		_strcpy(path, trans->string);
		_strcat(path, slash);
		_strcat(path, args[0]);
		if (check_file(path) == 0)
		{
			free_list(head);
			return (path);
		}
		free(path);
		path = NULL;
		trans = trans->next;
	}
	free_list(head);
	perror(argv);
	return (NULL);
}
/**
 * unsetenv_shell - unset environ variable
 * @f: arrays of argument pointers
 * @fst: name of the executable file
 *
 * Return: return integer value 1
 */
ssize_t unsetenv_shell(char **f, char *fst)
{
	unsigned int i = 0;
	char **store = NULL;

	if (!f[1] || args_count(f) != 2)
	{
		set_error(f[0], fst);
		return (1);
	}
	while (environ[i])
	{
		if (_strncmp(environ[i], f[1], _strlen(f[1])) ==  0)
		{
			free(environ[i]);
			store = &environ[i];
			++store;
			break;
		}
		i++;
	}
	while (environ[i])
	{
		environ[i] = *store;
		store++;
		i++;
	}
	return (1);
}
/**
 * _cd - changes directory
 * @f: arrays of pointers argument
 * @fst: name of the shell executable file
 *
 * Return: 1
 */
ssize_t _cd(char **f, char *fst)
{
	char *current_dir = _getenv("PWD"), *dir, **set_array_pwd, **set_array_oldpwd;

	dir = malloc(sizeof(char) * 1024);
	if (args_count(f) == 1)
	{
		if (f[1])
		{
			perror("too many arguments");
			return (1);
		}
	} else if (args_count(f) == 2)
	{
		if (f[2])
		{
			perror("Too many arguments");
			return (1);
		}
	}
	if (f[0] && !f[1])
		chdir(_getenv("HOME"));
	if (f[1])
		shorten(f[0], f[1], fst);
	set_array_oldpwd = init_args(dir, current_dir, 0);
	set_array_pwd = init_args(dir, current_dir, 1);
	setenv_shell(set_array_pwd, fst);
	setenv_shell(set_array_pwd, fst);
	free(set_array_oldpwd);
	free(set_array_pwd);
	free(dir);
	return (1);
}
/**
 * shorten - changes directory when directory is specified
 * @token: first argument
 * @value: name of directory
 * @fst: name of the shell executable file
 *
 * Return: void
 */
void shorten(char *token, char *value, __attribute__((unused))char *fst)
{
	char *current_dir, *new_dir = NULL, *slash, *home_dir, *target_dir;

	current_dir = _getenv("PWD");
	home_dir = malloc(sizeof(char) * 100);
	target_dir = malloc(sizeof(char) * 1024);
	slash = malloc(sizeof(char) * (_strlen(value) + 2));
	_strcat((_strcpy(home_dir, _getenv("HOME"))), "/");
	if ((value[0] == '-' && value[1] == '-') && !(value[2]))
		new_dir = home_dir;
	else if (value[0] == '-' && !(value[1]))
		new_dir = _getenv("OLDPWD");
	else if (value[0] == '~' && !(value[1]))
		new_dir = home_dir;
	else
	{
		_strcat(_strcpy(slash, "/"), value);
		_strcat((_strcpy(target_dir, current_dir)), slash);
	}
	if (new_dir == home_dir)
		chdir(home_dir);
	else if (new_dir == _getenv("OLDPWD"))
	{
		chdir(_getenv("OLDPWD"));
		write(STDOUT_FILENO, new_dir, strlen(new_dir));
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (access(target_dir, F_OK) == 0)
		chdir(target_dir);
	else if (!value || _strncmp(value, "$HOME", 5) == 0)
		chdir(home_dir);
	else
	{
		write(STDERR_FILENO, token, _strlen(token));
		write(STDERR_FILENO, ": can't cd to ", 14);
		write(STDERR_FILENO, value, _strlen(value));
		write(STDERR_FILENO, "\n", 2);
	}
	free(home_dir);
	free(target_dir);
	free(slash);
}
/**
 * set_error - set error messae for set and unset comnmand
 * @name: name of the command
 * @first_args: name of the shell executable file
 *
 * Return: return void
 */
void set_error(char *name, char *first_args)
{
	write(STDERR_FILENO, first_args, _strlen(first_args));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, name, _strlen(name));
	write(STDERR_FILENO, ": please type the correct syntax\n", 34);
}
