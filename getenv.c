#include "shell.h"

/**
 * _getenv - Retrieve the value of an environment variable.
 * @name: The name of the environment variable to search for.
 * @env: The array of environment variables.
 *
 * Return: A pointer to the value of the environment variable,
 *         or NULL if not found.
 */
char *_getenv(char *name, char *env[])
{
	int name_len = _strlen(name), i;
	char *variable;

	if (name == NULL || env == NULL)
		return (NULL);
	for (i = 0; env[i] != NULL; i++)
	{
		variable = env[i];

		if (_strncmp(variable, name, name_len) == 0 && variable[name_len] == '=')
			return (variable + name_len + 1);
	}
	return (NULL);
}
