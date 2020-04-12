#include "header.h"

int main(int argc, char **argv, char **env)
{
	char *cmd = "pwd";
	char *cmd_dir;
	(void)argv;
	(void)argc;
	
	cmd_dir = check_directory(cmd, env);
	printf("%s\n", cmd_dir);
	free(cmd_dir);

	return (0);
}
