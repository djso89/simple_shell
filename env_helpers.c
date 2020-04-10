#include "kshell.h"

/**
 * _getenv - takes the environment variable and turns it into a string
 * @name: environmental variable 
 * @env: environment vector
 * Return: value of environment name
 */

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