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

#define PATH_SIZE 200
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
	ssize_t (*ptr)(char **, char *);
} built_in;

/* function declarations */
extern char **environ;
char *getstring(char *string);
ssize_t execute(char **lineptr, char **argv);
void free_str(char **argv);
char *_getenv(char *env);
ssize_t built_commands(char **argv, char *);
ssize_t exit_shell(char **args, char *);
ssize_t check_file(char *filepath);
struct path_env *add_node_end(struct path_env **head, char *environ);
struct path_env *set_path();
ssize_t _execve_path(char **args, char *);
char *search_path(char **args, char *argv);
void free_list(struct path_env *head);
ssize_t env_shell(char **, char *);
ssize_t _cd(char **, char *);
size_t args_count(char **args);
void shorten(char *, char *, char *);
/* set enviroment varaible */
ssize_t setenv_shell(char **, char *);
void _setenv(char *name, char *value, size_t *n, char *address);
ssize_t unsetenv_shell(char **, char *first_args);
void set_error(char *, char *);
char **init_args(char *, char *, int);
#endif
