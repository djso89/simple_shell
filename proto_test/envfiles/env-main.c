#include <stdio.h>
#include <unistd.h>
/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	unsigned int i;
	(void)ac;
	(void)av;
	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	i = 0;
	printf("\n\n");
	while (__environ[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
