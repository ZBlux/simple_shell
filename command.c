#include "shell.h"

/**
 *execute_command- function that execute a command
 *
 *@command: the command entered
 *
 */
void execute_command(char *command)
{
	pid_t pid;
	char *argv[2];
	argv[0] = command;
	argv[1] = NULL;

	pid = fork();
	if (pid == 0)
	{
		if (access(argv[0], X_OK) == 0)
		{
			execve(argv[0], argv, NULL);
			perror("Error executing command");
		}
		else
		{
			perror("Command not found");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Fork error");
	}
	else
	{
		wait(NULL);
	}
}
