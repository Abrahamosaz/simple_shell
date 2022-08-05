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
	char slash[1] = "/", *path = NULL, *new_path = NULL;
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
		path = NULL;
		trans = trans->next;
	}
	free_list(trans);
	perror(argv);
	return (NULL);
}
