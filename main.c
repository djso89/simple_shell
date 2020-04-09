#include "kshell.h"
/**
 * main - entry point
 * @argc: argument count
 * @argv: argument values
 * @envp: environment values which are stored in here from start
 * Return: (0) Success
 */
int main(int argc, char **argv, char **envp)
{
	char *line = NULL;
	char **cmd;
	int done_status = 0;
	size_t n;
	ssize_t num_read;
	pid_t child;
	(void)argc;
	(void)argv;

	check_prompt();
	while ((num_read = getline(&line, &n, stdin)))
	{
		if (num_read == EOF)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		cmd = line_to_av(line);
		child = fork();
		if (child == 0)
		{
			if (execve(cmd[0], cmd, envp) == -1)
			{
				perror("Error");
			}
			return (1);
		}
		else
			wait(&done_status);
		free_av(cmd);
		fflush(stdin);
		check_prompt();
	}
	free_av(cmd);
	free(line);
	return (0);
}
