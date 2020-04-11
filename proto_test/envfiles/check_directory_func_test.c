#include "header.h"

int main(void)
{
	char *cmd = "ls";
	char *cmd_dir;

	cmd_dir = check_directory(cmd);
	printf("%s\n", cmd_dir);
	free(cmd_dir);

	return (0);
}
