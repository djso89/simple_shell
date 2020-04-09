#include "kshell.h"
/**
 * check_prompt - a function that prints the prompt as long as
 * file descriptor refers to a terminal (TTY)
 * Return: nothing
 */
void check_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "KuppaShell$ ", 12);
	}
}
