#include "kshell.h"

void sigintHandler(int sig_num)
{
	(void)sig_num;
    /* Reset handler to catch SIGINT next time.  */
	signal(SIGINT, sigintHandler);
	printf("\n Cannot be terminated using Ctrl+C \n");
	fflush(stdout);
	check_prompt();
}



/**
 * check_prompt - a function that print the prompt as long as
 * file descriptor refers to a terminal (TTY)
 * Return: Nothing
 */
void check_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "KuppaShell$ ", 12);
	}
}
/**
 * get_input - a function that gets string input in terminal
 * Return: string read from stdin. If getline fails, returns (NULL)
 */
char *get_input()
{
	char *line = NULL;
	size_t rd_cnt = 0;
	ssize_t num_read;

	num_read = getline(&line, &rd_cnt, stdin);
	if (num_read == -1)
		return (NULL);
	line[num_read - 1] = '\0';

	return (line);
}
/**
 * check_input - a function that checks if filename is valid
 * if the filename is found, returns appended string 
 * of address and / and cmd
 * @cmd: the user command such as ls pwd
 * @env: envirionment variable for getting direction from PATH env. variable
 * Return: appended string of directory and cmd with / in between.
 * if fails, it returns NULL
 */

char *check_input(char *cmd, char **env)
{
	char *dir_cmd;
	unsigned int i = 0;
	char **dir_av;
	struct stat st;

	if (cmd[0] == '/')
		return (_strdup(cmd));
	if (cmd[0] == '.' && cmd[1] == '/')
		return (_strdup(cmd));
	if (cmd[0] == '.' && cmd[1] == '.')
		return (_strdup(cmd));
	dir_av = get_dir(env);

	while (dir_av[i])
	{
		dir_cmd = get_dir_cmd(dir_av[i], cmd);
		if (!dir_cmd)
		{
			free_av(dir_av);
			return (NULL);
		}
		if (stat(dir_cmd, &st) == 0)
		{
			free_av(dir_av);
			return (dir_cmd);
		}
		free(dir_cmd);
		dir_cmd = NULL;
		i++;
	}
	free(dir_cmd);
	free_av(dir_av);
	return (NULL);

}
