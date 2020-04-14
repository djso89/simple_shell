#include "header.h"

int main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	char *path = "PATH";
	char *env_val = NULL;

	env_val = _getenv(path, env);
	printf("env[0] is %s\n", env[0]);
	printf("env_val is %s\n", env_val);

	return (0);
}
