#include "shell.h"

/**
 *main - Entry point for the simple shell program.
 *
 *Description : launching the programme
 *
 *@argc: The number of command-line arguments.
 *@argv: An array of strings containing the command-line arguments.
 *@env: An array of strings containing the environment variables.
 *
 *Return: 0 or -1
 */
int main(int argc, char *argv[], char *env[])
{
	(void)argc;

	command(argv, env);

	return (EXIT_SUCCESS);
}
