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
	/*int pgm_stat; exit_status = 0;cmd_num = 0; pid_t pgm; */
	(void)argc;
	(void)argv;
	(void)env;

	check_prompt();
	while (1)
	{
		num_read = getline(&line, &n, stdin);
		/*printf("line is %s\n", line);*/
		if (num_read == EOF)
		{
			write(STDOUT_FILENO, "\n", 1);
			free(line);
			break;
		}
		if (line[0] == '\n' || line[0] == ' ')
		{	fflush(stdin);
			check_prompt();
			continue;
		}
		line[num_read - 1] = '\0';
		av = line_to_av(line);
		free_av(av);
		check_prompt();
	}
	free(line);
	return (0);
}