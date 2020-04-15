#include "header.h"

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

	line = get_input();
	av = line_to_av(line);
	filename = check_input(av[0], env);
	/*check for error if usr command is in valid*/
	if (filename == NULL)
	{
		write(STDOUT_FILENO, "Error: ", 7);
		perror(av[0]);
	}
	printf("filename: %s\n", filename);
	free(filename);
	free(line);
	free_av(av);
	return (0);
}
