#include "shell.h"
/**
 * search_path - search for a particuler path that matches the command
 * @args: argument enter by the user
 *
 * Return: return pointer
 */
char *search_path(char **args)
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
			return (path);
		trans = trans->next;
	}
	perror(args[0]);
	return (NULL);
}
