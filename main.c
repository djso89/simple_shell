#include "kshell.h"
int check_spc_nl(char *line);
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
	int spc_flag = 0;
	(void)argc;
	(void)argv;
	(void)env;

	check_prompt();
	while ((num_read = getline(&line, &n, stdin)) != EOF)
	{
		/*printf("line is %s\n", line);*/
		spc_flag = check_spc_nl(line);
		if (spc_flag == 1)
		{
			spc_flag = 0;
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
