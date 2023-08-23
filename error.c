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
/**
 * custom_error - prints a custom error message
 * @cmd_name: the name of the command (argv[0])
 * @counter: the command counter
 * @error_msg: the error message to be printed
 */
void custom_error(char *cmd_name, int counter, char *error_msg)
{
	char counter_str[20];

	_itoa(counter, counter_str);

	_print_error(cmd_name);
	_print_error(": ");
	_print_error(counter_str);
	_print_error(": ");
	_print_error(error_msg);
	_print_error(": ");
	perror("");
}
