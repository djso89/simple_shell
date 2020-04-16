#include "kshell.h"
void check_exit(int ext_stat,char *cmd, char *line, char **av)
{
	if (cmd == NULL)
	{
		return;
	}
	/*check for exit routine*/
	if ((strncmp(cmd, "exit", _strlen(av[0])) == 0))
	{
		free(line);
		free_av(av);
		exit(ext_stat);
	}
}

int main(int argc, char **argv, char **env)
{

	(void)argc;
	(void)argv;
	char *line = NULL;
	char *filename;
	char **av;
	pid_t pgm;
	int pgm_run;
	int pgm_stat;
	int exit_status;

        
	while (1)
	{
		check_prompt();
		line = get_input();
		av = line_to_av(line);
		printf("av[0]: %s\n", av[0]);
		/*eof*/
		if (av[0] == NULL)
		{
			free(line);
			free_av(av);
			check_prompt();
			line = get_input();
			av = line_to_av(line);
			//av[0] = " ";
			continue;
		}
/**built-ins: cd, exit, env*/
		check_exit(exit_status,av[0], line, av);
/*check for error if usr command is in valid*/
		filename = check_input(av[0], env);
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
		line = NULL;
		free_av(av);
	}
	return (0);
}
