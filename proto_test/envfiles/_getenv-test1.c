#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char *_getenv(const char *name, char **env)
{
	char *env_name;
	char *env_tok;
	char *env_val;
	int i;

	env_name = malloc(sizeof(char) * (strlen(name) + 1));
	if (!env_name)
		return (NULL);
	strncpy(env_name, name, strlen(name) + 1);
	i = 0;
	env_tok = strtok(env[i],"=");
	while (env[i])
	{
		if (strcmp(env_tok, env_name) == 0)
		{
			env_tok = strtok(NULL, "\n");
			env_val = malloc(sizeof(char) * (strlen(env_tok) + 1));
			if (!env_val)
				return (NULL);
			strncpy(env_val, env_tok, (strlen(env_tok) + 1));
			return (env_val);
		}
		i++;
	        env_tok = strtok(env[i], "=");
	}
	free(env_name);
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
	/*we should get a string as /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
*/
	printf("%s\n", directories);
	free(directories);

	return (0);
}
