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
	char *line = NULL, *filename, **av;
	size_t n;
	ssize_t num_read;
	int exit_status = 0, spc_flag = 0, cmd_num = 0, i;
	(void)argc;

	check_prompt();
	while ((num_read = getline(&line, &n, stdin)) != EOF)
	{
		cmd_num++;
		spc_flag = check_spc_nl(line);
		if (spc_flag == 1)
		{
			spc_flag = 0;
			check_prompt();
			continue;
		}
		av = line_to_av(line);
		if (_strncmp(av[0], "exit", _strlen("exit")) == 0)
		{
			free_all(line, av);
			exit(exit_status);
		}
		filename = check_input(av[0], env);
		if (filename == NULL)
			exit_status = err_not_found(argv[0], av[0], cmd_num);
		else
		{
			exit_status = 0;
			free(av[0]);
			av[0] = _strdup(filename);
			i = execute(av, env, argv[0]);
			printf("i is %d\n", i);
		}
		free_all(filename, av);
		check_prompt();
	}
	check_EOF(num_read);
	free(line);
	return (exit_status);
}
