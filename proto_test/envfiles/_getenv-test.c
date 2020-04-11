#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	unsigned int i;
	char *path = "PATH";
	char *name;
	char *env_tok;
	(void)ac;
	(void)av;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	i = 0;

	name = malloc(sizeof(char) * (strlen(path) + 1));
	if (!name)
	{
		return (1);
	}


	strncpy(name, path, strlen(path));
	/*testing for iterating each lines in environment*/
	env_tok = strtok(env[i], "=");
	printf("%s\n", env_tok);
	i++;
	env_tok = strtok(env[i], "=");
	printf("%s\n", env_tok);
/**
	while (env[i] != NULL)
	{
		
		i++;
	}
**/
	//printf("%s\n", path);
	return (0);
}
