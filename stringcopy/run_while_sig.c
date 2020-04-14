#include "header.h"

void free_all(char **av, char *line)
{
        free_av(av);
	free(line);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char **av;
	char *line = NULL;
	pid_t pgm;
	int done_stat;
	int pgm_run;

	pgm_run = 0;
	done_stat = 0;
	signal(SIGINT, sigintHandler);
	check_prompt();
	while (1)
	{
		line = get_input();
		av = line_to_av(line);
		print_av(av);
		pgm = fork();

		if ((strcmp(av[0], "exit") == 0))
		{
			free_all(av, line);
			av = NULL;
			line = NULL;
			fflush(stdin);
			exit(EXIT_SUCCESS);
		}

		if (pgm == 0)
		{
			pgm_run = execve(av[0], av, env);
			if (pgm_run == -1)
			{
				perror("Error: oh no");
				free_all(av, line);
				line = NULL;
				av = NULL;
				printf("its freed\n");
			}
		}
		else
			wait(&done_stat);
		free_all(av, line);
		av = NULL;
		line = NULL;
		fflush(stdin);
		//line = NULL;
		//av = NULL;
		check_prompt();
	}
	return (0);

}
