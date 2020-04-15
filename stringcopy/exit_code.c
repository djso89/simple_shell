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
	char *cmd = "git";
        
	char *filename;

	filename = check_input(cmd, env);
	if (filename == NULL)
	{
		write(STDOUT_FILENO, "Error: ", 7);
		perror(cmd);
	}
	printf("filename: %s\n", filename);
	free(filename);

	return (0);
}
