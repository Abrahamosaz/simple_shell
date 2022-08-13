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
