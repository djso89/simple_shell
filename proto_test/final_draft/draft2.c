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
	char *filename;
	char **av;
	pid_t pgm;
	int pgm_run;
	int pgm_stat;
	while (1)
	{
		line = get_input();
		av = line_to_av(line);
		filename = check_input(av[0], env);
		/*check for error if usr command is in valid*/
		printf("filename: %s\n", filename);
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
			}
			else
				wait(&pgm_stat);
		}
		free(filename);
		free(line);
		free_av(av);
	}
	return (0);
}
