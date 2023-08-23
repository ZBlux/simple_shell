#include "shell.h"

/**
 *newline_removal- removes the newline character from a string.
 *
 *Description : replacing the new line with NULL
 *@str: The string to modify.
 *
 */
void newline_removal(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			break;
		}
		i++;
	}
}
/**
 *_print- writes string to the standar output
 *
 *@string: pointer to the array of chars
 *
 *Return: the number of bytes writed or -1
 */

int _print(char *string)
{
	return (write(STDOUT_FILENO, string, _strlen(string)));
}
/**
 *error_print- writes string to the standar error
 *
 *@string: pointer to the array of chars
 *
 *Return: the number of bytes writed or -1
 */

int error_print(char *string)
{
	return (write(STDERR_FILENO, string, _strlen(string)));
}
