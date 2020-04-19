#include "header.h"
/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int argc, char ** argv, char ** env)
{
	unsigned int i;
        char *env_val;
	(void)argv;
	(void)argc;

	i =47;
	env_val = _getenv("PATH",env);
	printf("env[%d]: %s\n",i, env[i]);
	printf("env value is %s\n", env_val);
	return (0);
}
