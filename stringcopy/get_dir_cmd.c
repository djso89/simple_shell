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

char *get_dir_cmd(char *dir, char *cmd)
{
	char *dir_cmd;
	unsigned int j;
	unsigned int k;

	dir_cmd = malloc(sizeof(char) * (strlen(cmd) + strlen(dir) + 2));
	if (!dir_cmd)
	{
		return (NULL);
	}
	for (j = 0; j < (strlen(dir) + strlen(cmd) + 1); j++)
	{
		dir_cmd[j] = '\0';
	}
	for (j = 0; j < strlen(dir); j++ )
	{
		dir_cmd[j] = dir[j];
		//printf("%c\n", dir_cmd[j]);
	}
	printf("j is at %d\n", j);
	dir_cmd[j] = '/';
	printf("after adding /: dir_cmd is %s\n", dir_cmd);
	printf("%c\n", dir_cmd[j]);
	j++;
	for (k = 0; k < strlen(cmd); k++)
	{
		dir_cmd[j + k] = cmd[k];
		//printf("dir_cmd[%d] is %c\n", j + k, dir_cmd[j + k]);
	}
	dir_cmd[j + k] = '\0';
	printf("after adding cmd: dir_cmd is %s\n", dir_cmd);

	return (dir_cmd);
}

int main(int argc, char **argv, char **env)
{

	(void)argc;
	(void)argv;
	char *cmd = "valgrind";
	char *dir_cmd;
	unsigned int i;
	char **dir_av;
//int isSame;
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
		printf("dir_cmd is %s\n", dir_cmd);
		free(dir_cmd);
		dir_cmd = NULL;
		i++;
	}
	free_av(dir_av);

	return (0);
}
