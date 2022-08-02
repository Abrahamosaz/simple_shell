#include "shell.h"
/**
 *
 *
 */
char *_getenv(const char *env)
{
	size_t i = 0, j, k;

	j = strlen(env);
	while (environ[i])
	{
		if (strncmp(environ[i], env, j) == 0)
		{
			for (k = 0; environ[i][k]; k++)
			{
				if (environ[i][k] == '=')
					return (&environ[i][++k]);
			}
		}
		i++;
	}
	return (NULL);
}
/**
 *
 *
 */
struct path_env *add_node_end(struct path_env **head, char *environ)
{
	struct path_env *dir = *head;
	struct path_env *new_node = NULL;


	new_node = malloc(sizeof(struct path_env));
	if (!new_node)
	{
		free(new_node);
		return (NULL);
	}
	_strcpy(new_node->string, environ);
	new_node->len = _strlen(environ);
	new_node->next = NULL;
	if (!*head)
	{
		*head = new_node;
		return (*head);
	}
	while (dir->next)
		dir = dir->next;
	dir->next = new_node;
	return (*head);
}
/**
 *
 *
 */
struct path_env *set_path(struct path_env **head)
{
	size_t i = 0;
	char *path;
	char *token, *delim =":";

	path = _getenv("PATH");
	token = strtok(path, delim);
	while (token)
	{
		add_node_end(head, token);
		token = strtok(NULL, delim);
	}
	return (*head);
}
/**
 *
 *
 */
ssize_t check_file(char *filepath)
{
	struct stat buffer;

	if (stat(filepath, &buffer) == 0)
		return (0);
	return (-1);
}
