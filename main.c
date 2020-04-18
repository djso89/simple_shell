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
     /* exit_status = 0;cmd_num = 0; */
	int spc_flag = 0;
	(void)argc;
	/*(void)env;*/

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
		execute(av, env, argv[0]);
		free_av(av);
		check_prompt();
	}
	check_EOF(num_read);
	free(line);
	return (0);
}
