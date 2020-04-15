#include "kshell.h"

void sigintHandler(int sig_num)
{
	(void)sig_num;
    /* Reset handler to catch SIGINT next time.  */
	signal(SIGINT, sigintHandler);
	printf("\n Cannot be terminated using Ctrl+C \n");
	fflush(stdout);
	check_prompt();
}



/**
 * check_prompt - a function that print the prompt as long as
 * file descriptor refers to a terminal (TTY)
 * Return: Nothing
 */
void check_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "KuppaShell$ ", 12);
	}
}
/**
 * get_input - a function that gets string input in terminal
 * Return: string read from stdin. If getline fails, returns (NULL)
 */
char *get_input()
{
	char *line = NULL;
	size_t rd_cnt = 0;
	ssize_t num_read;

	num_read = getline(&line, &rd_cnt, stdin);
	if (num_read == -1)
		return (NULL);
	line[num_read - 1] = '\0';

	return (line);
}
