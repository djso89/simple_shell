#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


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

void free_av(char **cmds)
{
	unsigned int i = 0;

	if (cmds == NULL)
		return;
	for (i = 0; cmds[i]; i++)
	{
		free(cmds[i]);
	}
	if (cmds[i] == NULL)
	{
		free(cmds[i]);
	}
	free(cmds);
}


/**
 * num_words - this function takes lines and counts number of words
 * @line: string line from the input
 * Return: Word counts
 */
unsigned int num_words(char *line, char delim)
{
	int fldelim = 0;
	unsigned int wc = 0;

	while (*line)
	{
		if (*line == delim)
			fldelim = 0;
		else if (fldelim == 0)
		{
			fldelim = 1;
			wc++;
		}
		++line;
	}
	return (wc);
}
/**
 * line_to_av - convert string into 2-D array arguments
 * @line: input string from user
 * Return: argument value vectors
 */
char **line_to_av(char *line)
{
	char *word = NULL;
	char **av;
	int ac = 0;
	int av_cnt = 0;
	char *line_cpy;
	
	ac = num_words(line, ' ');
	line_cpy = strdup(line);
	if (line_cpy == NULL)
	{
		return (NULL);
	}
//printf("%s\n",line);
	av = malloc(sizeof(char *) * (ac + 1));
	if (av == NULL)
	{
		free(line_cpy);
		return (NULL);
	}
	word = strtok(line_cpy, " ");
	//printf("%s\n", line);
	while (word)
	{
		av[av_cnt] = word;
		//printf("%s\n", av[av_cnt]);
		word = strtok(NULL, " ");
		av_cnt++;
	}
	av[av_cnt] = NULL;
	av_cnt = 0;
	free(line_cpy);
	return (av);
}



char *_getenv(const char *name, char **env)
{
	char *env_name;
	char *env_ret;
	unsigned int env_len;
	unsigned int i, j;

	i = 0;
	while (env[i])
	{
	        for (j = 0, env_len = 0; env[i][j] != '='; j++)
		{
			env_len++;
		}
		env_name = strndup(env[i], env_len);
		if (strcmp(env_name, name) == 0)
		{
			free(env_name);
			env_ret = strdup(env[i]);
			return (env_ret);
		}
		i++;
		//free(env_name);
	}
	free(env_name);
        return (NULL);
}
/**
 * check_directory- (char *user_cmd)
 * Description: this function returns string concatenate directory and file
 * @user_cmd: name of the program
 * Returns: string concatenate directory and file if the
 * usr_cmd exist in the directories char *user_cmd,
 */
char *check_directory(char *usr_cmd, char **env)
{
	char *dir;
	char **dir_av;
	char *dir_tok;
	int i;
	int num_dir;
	char *_cmd;

	dir = _getenv("PATH",env);
	printf("dir: %s\n", dir);
	num_dir = num_words(dir, ':');
	printf("number of directories = %d\n", num_dir);
	dir_av = malloc(sizeof(char *) * (num_dir + 1));
	if (dir_av == NULL)
	{
		free(dir);
		return (NULL);
	}
	/**convert single string dir to list of directories (in av format)**/
	dir_tok = strtok(dir, "=");
	dir_tok = strtok(NULL, ":");
	printf("dir: %s\n", dir);
        printf("%s\n", dir);
	i = 0;
	while (dir_tok)
	{
		dir_av[i] = malloc(strlen(dir_tok) + 1);
		if (dir_av[i] == NULL)
		{
			free(dir);
			free(dir_tok);
			return (NULL);
		}
		strncpy(dir_av[i], dir_tok, strlen(dir_tok) + 1);
	        printf("dir_av[%d]: %s\n",i ,dir_av[i]);
		dir_tok = strtok(NULL, ":");
		i++;
	}
	printf("dir_av[%d]: %s\n",i ,dir_av[i]);
	dir_av[i] = NULL;
	free(dir);
	i = 0;
	while (dir_av[i])
	{
		printf("dir_av[%d]: %s\n",i ,dir_av[i]);
		_cmd = malloc(sizeof(char) * (2 + strlen(dir_av[i]) + strlen(usr_cmd)));
		if (_cmd == NULL)
		{
			free_av(dir_av);
			return (NULL);
		}
		usr_cmd_dir(_cmd, dir_av[i], usr_cmd);
		if (access(_cmd, X_OK) == 0)
		{
			//free(dir);
		        free_av(dir_av);
			return (_cmd);
		}
		free(_cmd);
		i++;
	}
	free(dir);
	free(_cmd);
	free_av(dir_av);
	return (NULL);

}

#endif
