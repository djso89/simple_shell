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
	(void)argc;
	char *line, *filename;
	char **av;
	pid_t pgm;
	int pgm_stat, exit_status, cmd_num;

	cmd_num = 0;
	while (1)
	{
		cmd_num++;
		check_prompt();
		line = get_input(exit_status);
		if (line[0] == '\n')
			continue;
		av = line_to_av(line);
		if (strncmp(line, "env", _strlen(line)) == 0)
		{
			show_env(env, line, av);
			continue;
		}
		check_exit(exit_status, av[0], line, av);
		filename = check_input(av[0], env);
		if (filename == NULL)
		{
			errno_file(&exit_status, argv[0], av, line, cmd_num);
			continue;
		}
		if (access(filename, X_OK) != 0)
		{
			errno_perm(&exit_status, argv[0], av, line, cmd_num, filename);
			continue;
		}
		free(av[0]);
		av[0] = _strdup(filename);
		pgm = fork();
		pgm_stat = execute(pgm, av, line, env, filename);
		exit_status = get_exit_stat(pgm_stat);
		free3(line, av, filename);
	}
	return (0);
}
