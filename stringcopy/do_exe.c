#include "header.h"
void print_av(char **av)
{
	unsigned int i;

	for (i = 0; av[i]; i++)
	{
		printf("line 104: av[%d]: %s\n", i, av[i]);
	}
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char *line = NULL;
	char **av;
	size_t rd_cnt = 0;
	ssize_t num_read;

	pid_t pgm;
	int done_stat;
	int pgm_run;

	pgm_run = 0;
	done_stat = 0;
	do {
		num_read = getline(&line, &rd_cnt, stdin);
		line[num_read - 1] = '\0';
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
			}
		}
		else
		{
			wait(&done_stat);
			free_av(av);
		}
		fflush(stdin);
	} while (num_read != -1);

	free(line);
	fflush(stdin);
	fclose(stdin);

	return (0);

}
