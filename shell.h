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

/* function declarations */
extern char **environ;
int execute_command(char **argv);
char *getstring(char *string);
ssize_t execute(char *lineptr);
#endif
