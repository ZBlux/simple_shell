#include "shell.h"

/**
 *free_args - Frees the memory allocated for an array of strings.
 *
 *@argv: The array of strings to be freed.
 *
 */
void free_args(char *argv[])
{
	int i;

	if (argv == NULL)
	{
		return;
	}

	for (i = 0; argv[i] != NULL; i++)
	{
		free(argv[i]);
		argv[i] = NULL;
	}
}
/**
 *shell_exit - Clean up and exit the shell
 *
 *@cmd: The command string to free.
 *@args: The argument array to free.
 *
 */
void shell_exit(char *cmd, char *args[])
{
	if (_strcmp(cmd, "exit") == 0)
	{
		free_args(args);
		free(cmd);
		exit(EXIT_SUCCESS);
	}
}
