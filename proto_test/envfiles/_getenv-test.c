#include "header.h"
/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(void)
{
	unsigned int i;
        char *env_val;
	

	i =47;
	env_val = _getenv("PATH",environ);
	printf("env[%d]: %s\n",i, environ[i]);
	printf("env value is %s\n", env_val);
	return (0);
}
