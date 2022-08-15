#include "shell.h"
/**
 * free_str - free malloc memory allocated
 * @argv: argument stored on the heep by malloc
 *
 * Return: return void
 */
void free_str(char **argv)
{
	size_t count = 0, i;

	while (argv[count])
		count++;
	for (i = 0; i < count; i++)
	{
		free(argv[i]);
	}
	free(argv);
}
/**
 * free_list - free linked list
 * @head: head pointer of the linked list
 *
 * Return: return void
 */
void free_list(struct path_env *head)
{
	struct path_env *dir = head;

	while (dir)
	{
		dir = dir->next;
		free(head->string);
		free(head);
		head = dir;
	}
}
/**
 * init_args - init 2d array for setenv function called to change directory
 * @dir: allocated memory for getcwd function
 * @current_dir: point to the current direcctory
 * @check: to check which to initialise the array with
 *
 * Return: return a pointer to the 2d array
 */
char **init_args(char *dir, char *current_dir, int check)
{
	char **init = NULL;

	init = malloc(sizeof(char *) * 4);
	if (!init)
		return (NULL);
	init[0] = "setenv";
	if (check == 1)
	{
		init[1] = "PWD";
		init[2] = getcwd(dir, 1024);
		init[3] = NULL;
		return (init);
	}
	init[1] = "OLDPWD";
	init[2] = current_dir;
	init[3] = NULL;
	return (init);
}
