#include "kshell.h"
/**
 * sigintHandler - a function that handles Ctrl + C
 * @sig_num: not used
 * Return: Nothing
 */
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
 * check_spc_nl - function that checks if line has
 * bunch of spaces or just newline
 * @line: string from getline
 * Return: 1 if the line has many spaces or just a space or newline.
 * 0 if the line does not starts with newline
 */
int check_spc_nl(char *line)
{
	unsigned int i;

	i = 0;
	/*just look for spc and \n in starting char*/
	if ((line[0] == '\n' || line[0] == ' '))
	{
		if (line[0] == ' ' && _strlen(line) >= 2)
		{
			while (line[i] == ' ')
			{
				i++;
			}
			if (line[i] == '\n')
			{
				i = 0;
				return (1);
			}
			return (0);
		}
		if (_strlen(line) == 1)
		{
			return (1);
		}
	}
	return (0);
}
/**
 * execute - a function that execute the file name
 * @av: arguments in string
 * @env: environment strings
 * @argv0: executable file name.
 * Return: the status value obtained after program is done
 */
int execute(char **av, char **env, char *argv0)
{
	pid_t pgm;
	int pgm_stat;

	pgm = fork();
	if (pgm == 0)
	{
		if (execve(av[0], av, env) == -1)
			perror(argv0);
	}
	else
		wait(&pgm_stat);/*exit_status = WEXITSTATUS(pgm_stat);*/
	return (pgm_stat);
}
