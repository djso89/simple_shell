#include "kshell.h"
/**
 * main - Entry Point
 * @argc: number of argument count.
 * @argv: array of argument strings
 * @env: environment array of strings
 * Return: 0 (Success)
 */
int main(int argc, char **argv, char **env)
{
	char *line = NULL, **av;
	size_t n;
	ssize_t num_read;
	int pgm_stat, exit_status = 0;/*cmd_num = 0; */
	pid_t pgm;
	(void)argc;
	(void)argv;
	(void)env;

	check_prompt();
	while ((num_read = getline(&line, &n, stdin)) != EOF)
	{
		/*printf("line is %s\n", line);*/
		if (line[0] == '\n' || line[0] == ' ')
		{	fflush(stdin);
			check_prompt();
			continue;
		}
		line[num_read - 1] = '\0';
		av = line_to_av(line);

		pgm = fork();

		if (pgm == 0)
		{
			if (execve(av[0], av, NULL) == -1)
			{
				perror(argv[0]);
			}
		}
		else
			wait(&pgm_stat);
		exit_status = WEXITSTATUS(pgm_stat);
		printf("pgm exit is %d\n", exit_status);
		free_av(av);
		check_prompt();
	}
	/*write(STDOUT_FILENO, "\n", 1);*/
	printf("\npgm exit is %d\n", exit_status);
	free(line);
	return (0);
}
