#include "shell.h"
/**
 * execute - execute the command given to the shell
 * @lineptr: command string
 * @argv: command line arguments
 *
 * Return: return 0 on success and -1 otherwise
 */
ssize_t execute(char **lineptr, char **argv)
{
	ssize_t exit_status;
	char *new_path_env = NULL;
	pid_t childid;

	exit_status = built_commands(lineptr, argv[0]);
	if (exit_status != 0)
		return (exit_status);
	new_path_env = search_path(lineptr, argv[0]);
	if (!new_path_env)
		return (1);
	if (_strncmp(new_path_env, "find", 4) == 0)
	{
		exit_status = _execve_path(lineptr, argv[0]);
		return (exit_status);
	}
	childid = fork();
	if (childid == -1)
	{
		perror(argv[0]);
		return (-1);
	}
	if (childid == 0)
		execve(new_path_env, lineptr, environ);
	waitpid(childid, NULL, 0);
	free(new_path_env);
	return (1);
}
/**
 * _execve_path - execute command when path is passed by the user
 * @args: arguments pased by the user
 * @argv: first command line argument
 *
 * Return: return integer value
 */
ssize_t  _execve_path(char **args, char *argv)
{
	pid_t childid;

	childid = fork();
	if (childid == -1)
	{
		perror(argv);
		return (-1);
	}
	if (childid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror(argv);
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
int main(__attribute__((unused))int argc, char *argv[])
{
	ssize_t exit_status, output;
	size_t input;
	char *buffer = NULL, **tokens = NULL;

	do {
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "#cisfun$ ", 9);
		output = getline(&buffer, &input, stdin);
		if (output == -1)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		tokens = strtoken(buffer);
		exit_status = execute(tokens, argv);
		free_str(tokens);
		tokens = NULL;
		buffer = NULL;
	} while (exit_status != -1);
	exit(EXIT_SUCCESS);
}
