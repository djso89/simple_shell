#include "kshell.h"
/**
 * execute - a function that execute the file name
 * @pgm: child process
 * @av: arguments in string
 * @line: line string from getline
 * @env: environment strings
 * @fname: string from check_input to free if program fails
 * Return: the status value obtained after program is done
 */
int execute(pid_t pgm, char **av, char *line, char **env, char *fname)
{
	int stat = 0;
	int pgm_run;

	if (pgm == 0)
	{
		pgm_run = execve(av[0], av, env);
		if (pgm_run == -1)
		{
			perror("Error");
			free(line);
			free_av(av);
			free(fname);
			exit(126);
		}
	}
	else
		wait(&stat);

	return (stat);
}
