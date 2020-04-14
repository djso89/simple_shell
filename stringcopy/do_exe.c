#include "header.h"
void print_av(char **av)
{
	unsigned int i;

	for (i = 0; av[i]; i++)
	{
		printf("line 104: av[%d]: %s\n", i, av[i]);
	}
}
char *get_input()
{
	char *line;
	size_t rd_cnt = 0;
	ssize_t num_read;

	num_read = getline (&line, &rd_cnt, stdin);
	line[num_read - 1] = '\0';

	return (line);
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
	do {
		line = get_input();
		av = line_to_av(line);
		print_av(av);
		pgm = fork();
		if (pgm == 0)
		{
			pgm_run = execve(av[0], av, env);
			if (pgm_run == -1)
			{
				perror("Error: oh no");
				free_av(av);
				free(line);
			}
		}
		else
		{
			wait(&done_stat);
			free_av(av);
			free(line);
		}
		fflush(stdin);
	} while (line != NULL);

	free(line);
	fflush(stdin);
	fclose(stdin);

	return (0);

}
