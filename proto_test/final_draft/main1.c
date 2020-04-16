#include "kshell.h"


int main(int argc, char **argv, char **env)
{

	(void)argc;
	(void)argv;
	char *line = NULL;
	char *filename = NULL;
	char **av;
	pid_t pgm;
	int pgm_run = 0;
	int pgm_stat = 0;
	//ssize_t num_read;
	//size_t read_size;

	while (1)
	{
	        line = get_input();
		/*printf("line: %s\n", line);*/
		if (line[0] == '\n')
		{
			free(line);
			continue;
		}
		av = line_to_av(line);
		filename = check_input(av[0], env);
/*check for error if usr command is in valid*/
		if (filename == NULL)
		{
			write(STDOUT_FILENO, "Error: ", 7);
			perror(av[0]);
		}
		else
		{
			free(av[0]);
			av[0] = NULL;
			av[0] = strdup(filename);
			pgm = fork();
			
			if (pgm == 0)
			{
				pgm_run = execve(av[0], av, env);
				if (pgm_run == -1)
				{
					printf("failled\n");
				}
				return (1);
			}
			else
				wait(&pgm_stat);
		}
		free(filename);
		free(line);
		line = NULL;
		free_av(av);
	}
	return (0);
}
