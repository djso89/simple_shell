#include "kshell.h"


int main(int argc, char **argv, char **env)
{

	(void)argc;
	(void)argv;
	char *line;
	char *filename;
	char **av;
	pid_t pgm;
	int pgm_run;
	int pgm_stat;
	int exit_status;

	while (1)
	{
		line = get_input();
		av = line_to_av(line);
/**built-ins: cd, exit, env*/


		/*check for exit routine*/
		if ((strncmp(av[0], "exit", _strlen(av[0])) == 0))
		{
			free(line);
			free_av(av);
			exit(exit_status);
		}
/*check for error if usr command is in valid*/
		filename = check_input(av[0], env);
		printf("filename: %s\n", filename);
		if (filename == NULL)
		{
			exit_status = 127;
			write(STDOUT_FILENO, "Error: ", 7);
			perror(av[0]);
		}
		else
		{
			free(av[0]);
			av[0] = NULL;
			av[0] = _strdup(filename);
			pgm = fork();

			if (pgm == 0)
			{
				pgm_run = execve(av[0], av, env);
				if (pgm_run == -1)
				{
				printf("failled\n");
				}
			}
			else
			{
				wait(&pgm_stat);
				exit_status = 0;
			}
		}
		free(filename);
		free(line);
		free_av(av);
	}
	return (0);
}
