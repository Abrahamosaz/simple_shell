#include "shell.h"
/**
 * execute - execute the command given to the shell
 * @lineptr: command string
 *
 * Return: return 0 on success and -1 otherwise
 */
ssize_t execute(char *lineptr)
{
	unsigned int i = 0;
	struct stat statbuffer;
	char *args[] = {lineptr, NULL};
	pid_t childid;

	if (_strncmp(lineptr, "exit", 0) == 0)
		return (-1);
	childid = fork();
	if (childid == -1)
	{
		perror("Error");
		return (-1);
	}
	if (childid == 0)
	{
		if (stat(lineptr, &statbuffer) == 0)
		{
			execve(lineptr, args, environ);
		} else
		{
			perror(lineptr);
			exit(-1);
		}
	}
	waitpid(childid, NULL, 0);
	return (1);
}
/**
 * getstring - get the string from and remove the new line at the end
 * @string: buffer from getline function
 *
 * Return: return a memory on the heep
 */
char *getstring(char *string)
{
	char *buffer;
	size_t i = 0;

	while (string[i] != '\n')
		i++;
	buffer = malloc(sizeof(char) * i);
	i = 0;
	while (string[i] != '\n')
	{
		buffer[i] = string[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}
/**
 * main - main function of the shell program
 * @argc: number of argument to the program'
 * @argv: null terminated arguments
 *
 * Description: perform the required result
 *
 * Return: return an integer value
 */
int main(int argc, char *argv[])
{
	int  check = 1;
	ssize_t input, exit_status;
	size_t status = 0;
	char *buffer, *mallocmemory = NULL;
	struct stat statbuffer;

	do {
		if  (argc > 1)
		{
			if (stat(argv[1], &statbuffer) == 0)
				exit_status = execute_command(argv);
			else
			{
				perror("Error");
				exit_status = -1;
			}
		} else
		{
			write(STDOUT_FILENO, "#cisfun ", 8);
			input = getline(&buffer, &status, stdin);
			mallocmemory = getstring(buffer);
			exit_status = execute(mallocmemory);
		}
	} while (exit_status != -1);
	if (mallocmemory)
		free(mallocmemory);
	exit(EXIT_SUCCESS);
}
