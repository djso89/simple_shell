#include "kshell.h"

int get_exit_stat(int stat)
{
	if (stat == 256)
	        return (1);
	else if (stat == 512)
		return (2);
	else
	        return (0);
}


int main(int argc, char **argv, char **env)
{

	(void)argc;
	(void)argv;
	char *line;
	char *filename;
	char **av;
	pid_t pgm;
	int pgm_run;
	int pgm_stat;
	int exit_status = 0;

	while (1)
	{
		check_prompt();
		line = get_input(exit_status);
	        if (line[0] == '\n')
		{
			continue;
		}
		av = line_to_av(line);
/**built-ins: cd, exit, env*/
		check_exit(exit_status,av[0], line, av);
		filename = check_input(av[0], env);
		if (filename == NULL)
		{
			exit_status = 127;
			write(STDOUT_FILENO, "Error: ", 7);
			perror(av[0]);
		}
		else if(filename != NULL)
		{
			free(av[0]);
			av[0] = NULL;
			av[0] = _strdup(filename);
			pgm = fork();

			if (pgm == 0)
			{
				pgm_run = execve(av[0], av, env);
				if (pgm_run == -1)
				{
				perror("failled\n");
				}
			}
			else
			{
				wait(&pgm_stat);
				exit_status = 0;
			}
			exit_status = get_exit_stat(pgm_stat);
		}
		free(filename);
		free(line);
		free_av(av);
	}
	return (0);
}
