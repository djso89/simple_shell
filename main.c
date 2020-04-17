#include "kshell.h"

void check_EOF(ssize_t num_read);

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
	int pgm_stat;/* exit_status = 0;cmd_num = 0; */
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
				perror(argv[0]);
		}
		else
			wait(&pgm_stat);/*exit_status = WEXITSTATUS(pgm_stat);*/
		free_av(av);
		check_prompt();
	}
	check_EOF(num_read);
	free(line);
	return (0);
}
/**
 * check_EOF - a function that takes num_read from getline
 * and see if ctrl-D is pressed. if ctrl+D is pressed, it checks if
 * stdin file descriptor is on terminal.
 * @num_read: number of bytes read from getline
 * Return: nothing
 */
void check_EOF(ssize_t num_read)
{
	if (num_read == EOF)
	{
		if (isatty(STDIN_FILENO) != 0)
		{
			write(STDOUT_FILENO, "\n", 1);
		}
	}
}
