#include "shell.h"
/**
 * construct_full_path - Construct the full path of the command.
 * @path: The directory path.
 * @command: The name of the command.
 * Return: The full path of the command.
 */
char *construct_full_path(char *path, char *command)
{
	char *full_path = (char *)malloc(_strlen(path) + _strlen(command) + 2);

	if (!full_path)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	_strcpy(full_path, path);
	_strcat(full_path, "/");
	_strcat(full_path, command);
	return (full_path);
}

/**
 * check_and_strdup - Duplicate a string with error checking.
 * @string: The string to be duplicated.
 * Return: A pointer to the duplicated string.
 */
char *check_and_strdup(char *string)
{
	char *result = strdup(string);

	if (!result)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}

	return (result);
}

/**
 * search_command - Search for an executable command in PATH.
 * @command: The name of the command to search for.
 * Return: A pointer to the command if found, otherwise NULL.
 */
char *search_command(char *command)
{
	char *path_env = getenv("PATH");
	char *path;
	char *path_env_copy;
	char *result, *full_path;

	if (path_env == NULL)
	{
		perror("PATH not set");
		return (NULL);
	}
	path_env_copy = check_and_strdup(path_env);
	if (access(command, X_OK) == 0)
	{
		free(path_env_copy);
		return (check_and_strdup(command));
	}

	path = strtok(path_env_copy, ":");

	while (path != NULL)
	{
		full_path = construct_full_path(path, command);
		if (access(full_path, X_OK) == 0)
		{
			result = check_and_strdup(full_path);
			free(path_env_copy);
			free(full_path);
			return (result);
		}
		free(full_path);
		path = strtok(NULL, ":");
	}
	free(path_env_copy);
	return (NULL);
}
