#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

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
	char *env_val;
	int i;

	env_name = malloc(sizeof(char) * (strlen(name) + 1));
	if (!env_name)
		return (NULL);
	strncpy(env_name, name, strlen(name) + 1);
	i = 0;
	env_tok = strtok(env[i],"=");
	while (env[i])
	{
		if (strcmp(env_tok, env_name) == 0)
		{
			env_tok = strtok(NULL, "\n");
			env_val = malloc(sizeof(char) * (strlen(env_tok) + 1));
			if (!env_val)
				return (NULL);
			strncpy(env_val, env_tok, (strlen(env_tok) + 1));
			return (env_val);
		}
		i++;
	        env_tok = strtok(env[i], "=");
	}
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
		dir_cp = strdup(dir_av[i]);
		_cmd = strncat(dir_cp, "/", strlen("/"));
		_cmd = strncat(_cmd, usr_cmd, strlen(usr_cmd) + 1);

		if (access(_cmd, F_OK) == 0)
		{
		        free_av(dir_av);
			return (_cmd);
		}
		i++;
	}
	free(dir);
	free(_cmd);
	free_av(dir_av);
	return (NULL);

}
void check_prompt()
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "KuppaShell$ ", 12);
	}
}

int main(int argc, char **argv, char **envp)
{
	char *line = NULL;
	char *word;
	char **av;
	int ac;
	int av_cnt = 0;
	int done_status = 0;
	size_t n;
	ssize_t num_read;
	pid_t child;
	(void)argc;
	(void)argv;

	check_prompt();
	while ((num_read = getline(&line, &n, stdin)))
	{
		if (num_read == EOF)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		line[num_read - 1] = '\0';
		ac = num_words(line,' ');
		av = malloc(sizeof(char *) * (ac + 1));
		if (av == NULL)
		{
			free(line);
			return (1);
		}
		word = strtok(line, " ");

		while (word)
		{
			av[av_cnt] = malloc(strlen(word) + 1);
			if (av[av_cnt] == NULL)
			{
				free_av(av);
				return (1);
			}
			strncpy(av[av_cnt], word, strlen(word) + 1);
			word = strtok(NULL, " ");
			av_cnt++;
		}
		av[av_cnt] = NULL;
		av_cnt = 0;

		av[0] = check_directory(av[0],envp);
		printf("%s\n", av[0]);

	        /*creating process for executing program*/
		child = fork();
		if (child == 0)
		{
			if (execve(av[0], av, envp) == -1)
			{
				perror("Error");
			}
			printf("after execve\n");
			return (1);
		}
		else
			wait(&done_status);
	        free_av(av);
		fflush(stdin);
	        check_prompt();
	}
	free_av(av);
	free(line);

	return (0);
}
