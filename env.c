#include "shell.h"
/**
 * _getenv - get the value of the enviroment path variable
 * @env: key of the enviroment varaible
 *
 * Return: return pointer
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
 * add_node_end - add a node to the end of the linked list
 * @head: head pointer of the linked list
 * @environ: value to be strored
 *
 * Return: return a struct pointer
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
	new_node->string = environ;
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
 * set_path - set the path of the command enter by the user
 *
 * Return: return struct pointer
 */
struct path_env *set_path()
{
	char *path, *find;
	char *token, *delim = ":";
	struct path_env *path_var = NULL, *head = NULL;

	path = malloc(sizeof(char) * _strlen(_getenv("PATH")));
	if (!path)
	{
		free(path);
		return (NULL);
	}
	find = _getenv("PATH");
	_strcpy(path, find);
	token = strtok(path, delim);
	while (token)
	{
		head = add_node_end(&path_var, token);
		token = strtok(NULL, delim);
	}
	free(path);
	return (head);
}
/**
 * check_file - check a file if it exist
 * @filepath: the filepath to the file
 *
 * Return: return 0 if found and 1 otherwise
 */
ssize_t check_file(char *filepath)
{
	struct stat buffer;

	if (stat(filepath, &buffer) == 0)
		return (0);
	return (-1);
}
