#include "kshell.h"
/**
* _putchar - writes the character c to stdout
* @c: The character to print
*
* Return: On Success 1
* On error, -1 is returned, and errno is set appropriately
*/
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
* print_number - function
* Description: print the number
* @n: integer to print
* Return: nothing
*/
void print_number(int n)
{
	unsigned int k;
	/*check if n is negative*/
	if (n < 0)
	{
		_putchar('-');
		k = -n;
	}
	else
	{
		k = n;
	}
	/*remove the last digit*/
	if (k / 10 > 0)
	{
		print_number(k / 10);
	}
	/*print the last digit*/
	_putchar(k % 10 + '0');
}
/**
 * show_error - print out error message
 * @argv: object file name
 * @cmd: string from getline
 * @e_num: exit status value
 * @cmd_num: command number
 * Return: nothing
 */
void show_error(char *argv, char *cmd, int e_num, int cmd_num)
{
	write(STDOUT_FILENO, argv, _strlen(argv));
	write(STDOUT_FILENO, ": ", 2);
	print_number(cmd_num);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, cmd, _strlen(cmd));
	if (e_num == 126)
		write(STDOUT_FILENO, " Permission denied\n", 19);
	if (e_num == 127)
		write(STDOUT_FILENO, ": not found\n", 12);
}
/**
 * errno_file - print error when file does not exist and sets exit_status
 * @e_num: address of exit status
 * @argv0: object name in string
 * @av: array of argument string
 * @line: string from getline
 * @cmd_num: command number
 * Return: Nothing
 */
void errno_file(int *e_num, char *argv0, char **av, char *line, int cmd_num)
{
	*e_num = 127;
	show_error(argv0, av[0], *e_num, cmd_num);
	free_all(line, av);
}
/**
 * errno_perm - print error when file does not have permission to execute
 * then sets exit_status
 * @es: address of exit status
 * @argv0: object name in string
 * @av: array of argument string
 * @line: string from getline
 * @cn: command number
 * @fn: filename for freeing
 * Return: Nothing
 */
void errno_perm(int *es, char *argv0, char **av, char *line, int cn, char *fn)
{
	*es = 126;
	show_error(argv0, av[0], *es, cn);
	free_all(line, av);
	free(fn);
}
