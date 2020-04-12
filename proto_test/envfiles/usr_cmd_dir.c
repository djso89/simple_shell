#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * cmd_cpy - Function that copies a directory and user command
 * into a single line. This is later used to check if this is
 * a valid command to be executed
 * @dest: String containing directory and user command in one
 * @dir: Source: The directory string
 * @usr_cmd: Source: The user's input
 * Return: dest
 */
char *usr_cmd_dir(char *dest, char *dir, char *usr_cmd)
{
	int i, j;
	char fs = '/';

	for (i = 0; dir[i] != '\0'; i++)
		dest[i] = dir[i];

	dest[i] = fs;
	for (i++, j = 0; usr_cmd[j] != '\0'; j++, i++)
		dest[i] = usr_cmd[j];
	dest[i] = '\0';
	return (dest);
}

int main()
{
	char *cmd = "which";
	char *dir = "/bin";
	char *cmd_dir;
	unsigned int i = 0;

	cmd_dir = malloc(sizeof(char) + (strlen(cmd) + strlen(dir) + 2));
	if (!cmd_dir)
	{
	   return (1);
	}
	cmd_dir = usr_cmd_dir(cmd_dir, dir, cmd);
	printf("%s\n", cmd_dir);

	for (i = 0; i <= strlen(cmd_dir); i++)
	{
		printf("cmd_dir[%d]: %c\n", i, cmd_dir[i]);
	}

	free(cmd_dir);

	return (0);
}
