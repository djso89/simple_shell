#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void check_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "KuppaShell$ ", 12);
	}
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
        if(cmds[i] == NULL)
	{
		free(cmds[i]);
	}
	free(cmds);
}
void print_av(char **av)
{
	unsigned int i;

	for (i = 0; av[i]; i++)
	{
		printf("av[%d]: %s\n", i, av[i]);
	}
}
char *get_input()
{
	char *line = NULL;
	size_t rd_cnt = 0;
	ssize_t num_read;

	num_read = getline(&line, &rd_cnt, stdin);
	printf("num_read: %s and bytes: %ld\n", line, rd_cnt);
	if (num_read == -1)
		return (NULL);
	line[num_read - 1] = '\0';

	return (line);
}
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
	char **av;
        unsigned int wcnt;
	unsigned int i = 0;
	unsigned int j = 0;
	char *line_cp;
	char *word;

	line_cp = strdup(line);
	if (!line_cp)
		return (NULL);
/*start tokenizing and store into av format*/
	wcnt = 0;
	wcnt = num_words(line, ' ');
	printf("line 82: number of words: %u\n", wcnt);

	av = malloc(sizeof(char *) * (wcnt + 1));
	if (!av)
	{
		free(line_cp);
		return (NULL);
	}

	word = strtok(line_cp, " ");
		/*printf("word at first: %s\n", word);*/
	i = 0;
	j = 0;
	while (word)
	{
		printf("line 96: word: %s\n", word);
		av[i] = strdup(word);
		if (av[i] == NULL)
		{
			for (j = 0; j <= i; j++)
			{
				free(av[j]);
			}
			free(av);
			return (NULL);
		}
		word = strtok(NULL, " ");
		i++;
	}
	/*strtok and duplicate end*/
	free(line_cp);
	av[i] = NULL;
	return (av);
}

int _strncmp(const char* s1, const char* s2, size_t n)
{
    while(n--)
        if(*s1++!=*s2++)
            return *(unsigned char*)(s1 - 1) - *(unsigned char*)(s2 - 1);
    return (0);
}
char *_getenv(const char *name, char **env)
{
	char *env_name = NULL;
	unsigned int env_len;
	unsigned int i, j;
	int found;

	found = 0;
	i = 0;
	while (env[i])
	{
	        for (j = 0, env_len = 0; env[i][j] != '='; j++)
		{
			env_len++;
		}
		env_name = malloc(sizeof(char) * (env_len + 1));
		if (!env_name)
			return (NULL);
		env_name = strncpy(env_name, env[i] ,env_len);
		found = _strncmp(env_name, name, env_len);
		if ( found == 0)
		{
			printf("found at: %d\n", i);
			free(env_name);
			return (env[i]);
		}
		i++;
		free(env_name);
		env_name = NULL;
	}
        return (NULL);
}

/*signal stuff*/
/* Signal Handler for SIGINT */
static void sigintHandler(int sig_num) 
{
	(void)sig_num;
    /* Reset handler
       to catch SIGINT next time.  */
    signal(SIGINT, sigintHandler);
    printf("\n Cannot be terminated using Ctrl+C \n");
    fflush(stdout);
    check_prompt();
}


/*directory helpers*/

unsigned int get_num_dir(char *dir)
{
	unsigned int dir_len;
	char *dir_cpy;
	char *dir_tok;
	int dir_num;
	

	dir_len = strlen(dir);
	/*copy the PAth string*/
	dir_cpy = malloc(sizeof(char) * (dir_len + 1));
	if (!dir_cpy)
	{
		return (1);
	}
	dir_cpy = strncpy(dir_cpy, dir, dir_len + 1);

/*parse string into array of strings*/
	dir_tok = strtok(dir_cpy, "=");
	for (dir_tok = strtok(NULL, ":"),
		    dir_num = 0;
	     dir_tok;
	     dir_num++,
		     dir_tok = strtok(NULL, ":"))
	{
		printf("dir_tok: %s\n", dir_tok);
	}
	free(dir_cpy);
	return (dir_num);
}
#endif /*HEADER_H */
