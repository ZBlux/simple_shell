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
	int is_interactive = isatty(STDIN_FILENO), count = 0;

	while (1)
	{
		count++;
		if (is_interactive)
			_print("#cisfun$ ");


		size = getline(&cmd, &n, stdin);
		if (size == -1)
		{
			free(cmd);
			free_args(args);
			exit(EXIT_FAILURE);
		}

		newline_removal(cmd);
		if (_strlen(cmd) == 0 || _strspn(cmd, " \t\n\v\f\r") == _strlen(cmd))
			continue;
		tokenize_command(cmd, args);
		execute_and_wait(args, env, argv);
		free_args(args);
	}
}
/**
 * execute_and_wait - Forks a child process,
 * executes a command, and waits for the child to complete.
 * @args: Array of strings containing the command and arguments.
 * @env: Array of strings containing environment variables.
 * @argv: Array of strings containing command-line arguments.
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
 * execute_command - Executes a command using execve.
 * @args: Array of strings containing the command and its arguments.
 * @env: Array of strings containing environment variables.
 * @command: command to execute
 *
 * Description: Executes the command specified in the args array
 * using the execve system call. Prints an error message if the
 * command execution fails.
 */
void execute_command(char *command, char *args[], char *env[])
{
	if (execve(command, args, env) == -1)
	{
		exit(EXIT_FAILURE);
	}
}

/**
 * tokenize_command - Tokenizes a command string into an array of strings.
 * @command: The command string to tokenize.
 * @args: An array of strings to store the tokenized command.
 *
 * Description: This function splits the input command string into tokens
 * using space characters as delimiters. Each token is dynamically allocated
 * using strdup and stored in the args array. The last element of the args
 * array is set to NULL to indicate the end of the array. If memory allocation
 * fails, an error message is printed and the program exits with EXIT_FAILURE.
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
 * Return: A dynamically allocated string containing the full path
 *         to the executable command if found,
 *         or NULL if the command was not found in any of the directories.
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
