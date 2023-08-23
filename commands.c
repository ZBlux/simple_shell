#include "shell.h"

/**
 *command- Implements a simple shell prompt.
 *
 *@argv: array of strings containing command-line arguments.
 *@env: array of strings containing environment variables.
 *
 */
void command(char *argv[], char *env[])
{
	char *cmd = NULL;
	size_t n = 0;
	ssize_t size;
	char *args[] = {NULL, NULL, NULL};
	int is_interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (is_interactive)
		{
			_print("#cisfun$ ");
		}
		size = getline(&cmd, &n, stdin);

		if (size == -1)
		{
			if (feof(stdin))
			{
				free(cmd);
				free_args(args);
				exit(EXIT_SUCCESS);
			}
			else
			{
				free_args(args);
				free(cmd);
				exit(EXIT_FAILURE);
			}
		}
		newline_removal(cmd);
		if (_strlen(cmd) == 0 || _strspn(cmd, " \t\n\v\f\r") == _strlen(cmd))
			continue;
		if (strcmp(cmd, "exit") == 0)
		{	free_args(args);
			free(cmd);
			exit(EXIT_SUCCESS);
		}
		tokenize_command(cmd, args);
		execute_and_wait(args, env, argv);
		free_args(args);
	}
}
/**
 *execute_and_wait - Forks a child process,
 *
 *@args: Array of strings containing the command and arguments.
 *@env: Array of strings containing environment variables.
 *@argv: Array of strings containing command-line arguments.
 *
 */
void execute_and_wait(char *args[], char *env[], char *argv[])
{
	pid_t new_pro;
	int status;
	char *command = search_command(args[0]);

	(void)argv;
	if (command == NULL)
	{
		free(command);
		return;
	}
	new_pro = fork();
	if (new_pro == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (new_pro == 0)
	{
		execute_command(command, args, env);
	}
	else
	{
		wait(&status);
		free(command);
	}
}

/**
 *execute_command- executes a command using execve.
 *
 *@args: Array of strings containing the command and its arguments.
 *@env: Array of strings containing environment variables.
 *@command: command to execut
 *
 */
void execute_command(char *command, char *args[], char *env[])
{
	if (execve(command, args, env) == -1)
	{
		exit(EXIT_FAILURE);
	}
}

/**
 *tokenize_command- tokenizes a command string into an array of strings.
 *
 *@command: The command string to tokenize.
 *@args: An array of strings to store the tokenized command.
 *
 */
void tokenize_command(char *command, char *args[])
{
	char *token = strtok(command, " ");

	int index = 0;

	while (token != NULL)
	{
		if (_strlen(token) > 0)
		{
			args[index] = _strdup(token);
			if (args[index] == NULL)
			{
				perror("strdup");
				free_args(args);
				exit(EXIT_FAILURE);
			}
		}
		index++;
		token = strtok(NULL, " ");
	}

	args[index] = NULL;
}

/**
 * search_command - Search for an executable command in the directories
 *          listed in the PATH environment variable.
 * @command: The name of the command to search for.
 *
 * Return: result or NULL
 */
char *search_command(char *command)
{
	char *path_env = getenv("PATH");
	char *path_env_copy = strdup(path_env);
	char *path = strtok(path_env_copy, ":");
	char *full_path = NULL;
	char *result = NULL;

	if (access(command, X_OK) == 0)
                return (_strdup(command));

	while (path != NULL)
	{
		full_path = (char *)malloc(_strlen(path) + _strlen(command) + 2);
		if (full_path == NULL)
		{
			free(path_env_copy);
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		_strcpy(full_path, path);
		_strcat(full_path, "/");
		_strcat(full_path, command);
		if (access(full_path, X_OK) == 0)
		{
			result = strdup(full_path);
			if (result == NULL)
			{free(path_env_copy);
				perror("strdup");
				free(full_path);
				exit(EXIT_FAILURE);
			}
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
