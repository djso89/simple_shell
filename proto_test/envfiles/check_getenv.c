#include "header.h"
/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	const char *env_var = "PATH";
	char *env_val;

	(void)ac;
	(void)av;

        env_val = _getenv(env_var);
	if (env_val == NULL)
	{
		printf("not found\n");
	}
	else
	{
		printf("%s\n", env_val);
	}
	//free(env_val);

	return (0);
}
