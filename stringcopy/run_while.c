#include "header.h"
void print_av(char **av)
{
	unsigned int i;

	for (i = 0; av[i]; i++)
	{
		printf("av[%d]: %s\n", i, av[i]);
	}
}
char *get_input()
{
	char *line = NULL;
	size_t rd_cnt = 0;
	ssize_t num_read;

	num_read = getline(&line, &rd_cnt, stdin);
	printf("num_read: %s and bytes: %ld\n", line, rd_cnt);
	if (num_read == -1)
		return (NULL);
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
	while (1)
	{
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
				free(line);
				free_av(av);
				line = NULL;
				av = NULL;
				printf("its freed\n");
			}
		}
		else
			wait(&done_stat);
		free_av(av);
		free(line);
		av = NULL;
		line = NULL;
		fflush(stdin);
		//line = NULL;
		//av = NULL;
	}
	return (0);

}
