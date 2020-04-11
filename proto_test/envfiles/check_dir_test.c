#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
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

char *_getenv(const char *name, char **env)
{
	char *env_name;
	char *env_tok;
	int i;

	env_name = malloc(sizeof(char) * (strlen(name) + 1));
	if (env_name == NULL)
		return (NULL);
	strncpy(env_name, name, strlen(name) + 1);
	i = 0;
	env_tok = strtok(env[i],"=");
	while (env[i])
	{
		if (strcmp(env_tok, env_name) == 0)
		{
			env_tok = strtok(NULL, "\n");
			free(env_name);
			return (env_tok);
		}
		i++;
	        env_tok = strtok(env[i], "=");
	}
	free(env_tok);
	free(env_name);
        return (NULL);
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


char **line_to_av(char *line)
{
	char *word = NULL;
	char **av;
	int ac = 0;
	int av_cnt = 0;

	ac = num_words(line, ' ');
	av = malloc(sizeof(char *) * (ac + 1));
	if (av == NULL)
	{
		free(line);
		return (NULL);
	}
	word = strtok(line, " ");

	while (word)
	{
		av[av_cnt] = malloc(strlen(word) + 1);
		if (av[av_cnt] == NULL)
		{
			free_av(av);
			return (NULL);
			}
		strncpy(av[av_cnt], word, strlen(word) + 1);
		word = strtok(NULL, " ");
		av_cnt++;
	}
	av[av_cnt] = NULL;
	av_cnt = 0;

	return (av);
}

/**
 * check_directory- (char *user_cmd)
 * Description: this function returns string concatenate directory and file
 * @user_cmd: name of the program
 * Returns: string concatenate directory and file if the
 * usr_cmd exist in the directories char *user_cmd,
 */
char *check_directory(char *usr_cmd,  char **env)
{
	char *dir;
	char **dir_av;
	char *dir_tok;
	int i;
	int num_dir;

	char *_cmd;
	char *dir_cp;
	dir = _getenv("PATH", env);
	num_dir = num_words(dir, ':');
	dir_av = malloc(sizeof(char *) * (num_dir + 1));
	if (dir_av == NULL)
	{
		free(dir);
		return (NULL);
	}
	/**convert single string dir to list of directories (in av format)**/
	dir_tok = strtok(dir, ":");
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
		strncpy(dir_av[i], dir_tok, strlen(dir_tok));
		dir_tok = strtok(NULL, ":");
		i++;
	}
	dir_av[i] = NULL;

	i = 0;

	while (dir_av[i])
	{
		/*contatenate current dir_av value with cmd*/
		_cmd = malloc(sizeof(char) * (2 + strlen(dir_av[i])));
		if (_cmd == NULL)
		{
			free_av(dir_av);
			return (NULL);
		}
		dir_cp = strdup(dir_av[i]);//replace this with strncpy
		_cmd = strncat(dir_cp, "/", strlen("/"));
		_cmd = strncat(_cmd, usr_cmd, strlen(usr_cmd) + 1);

		if (access(_cmd, F_OK) == 0)
		{
			//free(dir_cp);
		        free_av(dir_av);
			return (_cmd);
		}
		i++;
	}
	free(_cmd);
	free_av(dir_av);
	return (NULL);

}

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	const char *env_var = "klwer";
	char *env_val;

	(void)ac;
	(void)av;

        env_val = _getenv(env_var, env);

	printf("%s\n", env_val);
	//free(env_val);

	return (0);
}
