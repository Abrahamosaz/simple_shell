#ifndef SHELL_H
#define SHELL_H
/* headers files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include "string.h"

/* defined macro */
#define READSIZE 1024
#define PATH_SIZE 50

/* struct for enviroment variable */
/**
 * struct path_env - struct that store the path value
 * @string: each path avaliable to the shell
 * @len: the length of the paths
 * @next: pointer to struct path_env
 */
struct path_env
{
	char *string;
	unsigned int len;
	struct path_env *next;
};

/* buitin commands */
/**
 * struct built_in - struct for builtin commands in the shell
 * @_command: command passed by the user
 * @ptr: function pointer
 */
typedef struct built_in
{
	char *_command;
	ssize_t (*ptr)();
} built_in;

/* function declarations */
extern char **environ;
int execute_command(char **argv);
char *getstring(char *string);
ssize_t execute(char **lineptr);
void free_str(char **argv);
char *_getenv(const char *env);
ssize_t built_commands(char **argv);
ssize_t exit_shell(char **args);
ssize_t check_file(char *filepath);
struct path_env *add_node_end(struct path_env **head, char *environ);
struct path_env *set_path();
ssize_t _execve_path(char **args);
char *search_path(char **args);
#endif
