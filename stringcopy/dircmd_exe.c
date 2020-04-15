#include "header.h"



int main(int argc, char **argv, char **env)
{

	(void)argc;
	(void)argv;
	char *cmd = "ls";
	char *dir_cmd;
	unsigned int i;
	char **dir_av;

	dir_av = get_dir(env);
	print_av(dir_av);
	i = 0;
	while (dir_av[i])
	{
		dir_cmd = get_dir_cmd(dir_av[i], cmd);
		if (!dir_cmd)
		{
			free_av(dir_av);
			return (1);
		}
		printf("dir_cmd is %s\n\n\n\n", dir_cmd);

		if (access(dir_cmd, F_OK) == 0)
		{
			printf("Found %s in %s\n", cmd, dir_av[i]);
			break;
		}
		free(dir_cmd);
		dir_cmd = NULL;
		i++;
	}
	free(dir_cmd);
	free_av(dir_av);

	return (0);
}
