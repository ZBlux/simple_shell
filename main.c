#include "shell.h"

/**
 *main- command line interpreter
 *
 *
 *Return: 0
 */
int main(void)
{
	char line[1024];
	ssize_t n;

	while (1)
	{
		printf("#cisfun$ ");
		n = read(STDIN_FILENO, line, sizeof(line));
		if (n == 0)
			break;
		line[n - 1] = '\0';
		execute_command(line);
		printf("#cisfun$ ");
	}
	return (0);
}
