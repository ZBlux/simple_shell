#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

extern char **environ;

/*Function prototypes*/
void command(char *argv[], char *env[]);
void execute_command(char *command, char *args[], char *env[]);
void execute_and_wait(char *args[], char *env[], char *argv[]);
void tokenize_command(char *command, char *args[]);
char *search_command(char *command);
void free_args(char *argv[]);
void newline_removal(char *str);

int _putchar(char c);
void _puts(char *str);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
int _strspn(const char *str1, const char *str2);
char *_strstr(char *haystack, char *needle);
char *_strdup(const char *src);
char *_strcat(char *dest, const char *src);

#endif
