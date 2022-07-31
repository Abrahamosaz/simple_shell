#include "shell.h"
/**
 * execute - execute the command given to the shell
 * @lineptr: command string
 *
 * Return: return 0 on success and -1 otherwise
 */
ssize_t execute(char **lineptr)
{
	unsigned int i = 0;
	struct stat statbuffer;
	pid_t childid;

	if (_strncmp(lineptr[0], "exit", 0) == 0)
	{
		return (-1);
	}
	childid = fork();
	if (childid == -1)
	{
		perror("Error");
		return (-1);
	}
	if (childid == 0)
	{
		if (stat(lineptr[0], &statbuffer) == 0)
		{
			execve(lineptr[0], lineptr, environ);
		} else
		{
			perror(lineptr[0]);
			exit(-1);
		}
	}
	waitpid(childid, NULL, 0);
	return (1);
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
	char *buffer = NULL;
	char **tokens = NULL;
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
			if (input == -1)
			{
				free(buffer);
				return (0);
			}
			tokens = strtoken(buffer);
			exit_status = execute(tokens);
			free_str(tokens);
			free(buffer);
			tokens = NULL;
			buffer = NULL;
		}
	} while (exit_status != -1);
	exit(EXIT_SUCCESS);
}
