#include "header.h"

char **get_dir(char **env)
{
	unsigned int dir_num;
	char *dir;
	char *dir_cpy;
	char *dir_tok;
	char **dir_av;
	unsigned int i = 0;

	dir = _getenv("PATH", env);
	dir_num = get_num_dir(dir);
	dir_cpy = malloc(sizeof(char) * (strlen(dir) + 1));
	if (!dir_cpy)
		return (NULL);
	dir_cpy = strncpy(dir_cpy, dir, (strlen(dir) + 1));
	dir_tok = strtok(dir_cpy, "=");
	dir_tok = strtok(NULL, ":");
	dir_av = malloc(sizeof(char *) * (dir_num + 1));
	if (!dir_av)
	{
		free(dir_cpy);
		return (NULL);
	}
	while (dir_tok)
	{
		dir_av[i] = malloc(sizeof(char) * (strlen(dir_tok) + 1));
		if (!dir_av[i])
		{
			free_upto_n(dir_av, i);
			return (NULL);
		}
		dir_av[i] = strncpy(dir_av[i], dir_tok, strlen(dir_tok) + 1);
		dir_tok = strtok(NULL, ":");
		i++;
	}
	dir_av[i] = NULL;
	free(dir_cpy);

	return (dir_av);
}



int main(int argc, char **argv, char **env)
{

	(void)argc;
	(void)argv;
	char *cmd = "ls";
	char *dir_cmd;
	char **dir_av;
	int isSame;
        
	dir_av = get_dir(env);
	print_av(dir_av);

	free_av(dir_av);

	return (0);
}
