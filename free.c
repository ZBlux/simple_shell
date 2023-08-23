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
	free(argv);
}
