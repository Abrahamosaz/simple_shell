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
	ssize_t exit_status;
	char *new_path_env = NULL;
	pid_t childid;

	exit_status = built_commands(lineptr);
	if (exit_status == -1)
		return (exit_status);
	new_path_env = search_path(lineptr);
	if (!new_path_env)
		return (1);
	if (_strncmp(new_path_env, "find", 4) == 0)
	{
		exit_status = _execve_path(lineptr);
		return (exit_status);
	}
	childid = fork();
	if (childid == -1)
	{
		perror("Error");
		return (-1);
	}
	if (childid == 0)
		execve(new_path_env, lineptr, environ);
	waitpid(childid, NULL, 0);
	return (1);
}
/**
 * _execve_path - execute command when path is passed by the user
 * @args: arguments pased by the user
 *
 * Return: return integer value
 */
ssize_t  _execve_path(char **args)
{
	pid_t childid;

	childid = fork();
	if (childid == -1)
	{
		perror("Error");
		return (-1);
	}
	if (childid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror(args[0]);
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
	ssize_t input, exit_status;
	size_t status = 0;
	char *buffer = NULL, **tokens = NULL;
	struct stat statinfo;

	do {
		if  (argc > 1)
		{
			if (stat(argv[1], &statinfo) == 0)
				exit_status = execute_command(argv);
			else
			{
				perror("Error");
				exit_status = -1;
			}
		} else
		{
			write(STDOUT_FILENO, "#cisfun ", 8);
			input = getline(&buffer, &input, stdin);
			if (input == -1)
			{
				free(buffer);
				exit(EXIT_SUCCESS);
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
