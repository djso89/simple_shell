#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * _getenv - function that gets the value of environment variable name
 * @name: environment variable string
 * @env: environment array of strings
 * Return: environment value string. if not found, return NULL
 */
char *_getenv(const char *name, char **env)
{
	char *env_name = NULL;
	unsigned int env_len;
	unsigned int i, j;
	int found;

	if (!env)
		return (NULL);
	found = 0;
	i = 0;
	while (env[i])
	{
		printf("in while (env[i]\n");
		for (j = 0, env_len = 0; env[i][j] != '='; j++)
		{
			env_len++;
		}
		env_name = malloc(sizeof(char) * (env_len + 1));
		if (!env_name)
			return (NULL);
		env_name = strncpy(env_name, env[i], env_len);
		found = strncmp(env_name, name, env_len);
		if (found == 0)
		{
			free(env_name);
			return (env[i]);
		}
		i++;
		free(env_name);
		env_name = NULL;
	}
	return (NULL);
}



#endif /*HEADER_H*/
