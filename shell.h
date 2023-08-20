#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

/*Function prototypes*/
void execute_command(char *command);


int _putchar(char c);
void _puts(char *str);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);

#endif
