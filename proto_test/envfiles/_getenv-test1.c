#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char *_getenv(const char *name, char **env)
{
	char *env_tok;
	char *env_name;
	int i, j, name_len;

	env_name = NULL;
	i = 0;
	j = 0;
	name_len = strlen(name);

	while (env[i])
	{
		while(j < name_len)
		{
			env_name[j] = env[i][j];
			j++;
		}
		if (strcmp(env_name, name) == 0)
		{
			return (env[i]);
		}
		i++;
	}
        return (NULL);
}

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	//unsigned int i;
	//char *path = "LOGNAME"; //should print out seat0
        
	char *directories;
	(void)ac;
	(void)av;


        directories = _getenv("LOGNAME",env);
	printf("%s\n", directories);
        

	return (0);
}
