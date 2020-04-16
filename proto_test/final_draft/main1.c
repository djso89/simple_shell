#include "kshell.h"

char *check_input(char *cmd, char **env)
{
	char *dir_cmd;
	unsigned int i = 0;
	char **dir_av;
	struct stat st;

	if (cmd[0] == '/')
		return (strdup(cmd));
	if (cmd[0] == '.' && cmd[1] == '/')
		return (strdup(cmd));
	if (cmd[0] == '.' && cmd[1] == '.')
		return (strdup(cmd));
	dir_av = get_dir(env);

	while (dir_av[i])
	{
		dir_cmd = get_dir_cmd(dir_av[i], cmd);
		if (!dir_cmd)
		{
			free_av(dir_av);
			return (NULL);
		}
		if (stat(dir_cmd, &st) == 0)
		{
			free_av(dir_av);
			return (dir_cmd);
		}
		free(dir_cmd);
		dir_cmd = NULL;
		i++;
	}
	free(dir_cmd);
	free_av(dir_av);
	return (NULL);

}


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
	ssize_t num_read;
	size_t read_size;

	num_read = getline(&line, &read_size, stdin);
	do {
		if (line[0] == '\n')
		{
			//free_av(av);
			//free(line);
			printf("av[0] is null\n");
			continue;
		}
		if (num_read == EOF)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		printf("line: %s", line);
		
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
	}while ((num_read = getline(&line, &read_size, stdin)));
	return (0);
}
