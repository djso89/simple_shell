#include "header.h"


int main(int argc, char **argv, char **env)
{

	(void)argc;
	(void)argv;
//	char *cmd = "ls";
	unsigned int dir_num;
	char *dir;
	char *dir_cpy;
	char *dir_tok;
	char **dir_av;
	unsigned int i, j;
	unsigned int len = 0;

	dir = _getenv("PATH", env);
        dir_num = get_num_dir(dir);
	dir_cpy = malloc(sizeof(char) * (strlen(dir) + 1));
	if (!dir_cpy)
		return (1);
	dir_cpy = strncpy(dir_cpy, dir, (strlen(dir) + 1));
	dir_tok = strtok(dir_cpy, "=");
	dir_tok = strtok(NULL, ":");
	printf("%s\n", dir_tok);
/*allocate array of strings with dir_num*/
	
	dir_av = malloc(sizeof(char *) * (dir_num + 1));
	if (!dir_av)
	{
		free(dir_cpy);
		return (1);
	}
	i = 0;
	while (dir_tok)
	{
		//len = 0;
	        printf("In a while loop, dir_tok is %s\n", dir_tok);
		len = strlen(dir_tok);
		printf("length of current dir_tok is %d\n", len);
		dir_av[i] = malloc(sizeof(char) *(strlen(dir_tok) + 1));
		if (!dir_av[i])
		{
			for (j = 0; j <= i; j++)
				free(dir_av[j]);
			free(dir_av);
			return (1);
		}
		dir_av[i] = strncpy(dir_av[i], dir_tok, strlen(dir_tok)+1);
		dir_tok = strtok(NULL, ":");
		i++;
	}
	dir_av[i] = NULL;
	for (i = 0; dir_av[i]; i++)
		printf("dir_av[%d]: %s\n", i, dir_av[i]);
	free(dir_cpy);
	dir_cpy = NULL;
	free_av(dir_av);
	return (0);
}
