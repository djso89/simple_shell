#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>


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
	unsigned int i;
	unsigned int j;
	char *line_cp;
	char *word;

	line_cp = strdup(line);
	if (!line_cp)
	{
		return (NULL);
	}
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


char *_getenv(const char *name, char **env)
{
	char *env_name;
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
		found = strcmp(env_name, name);
		if ( found == 0)
		{
			free(env_name);
			return (env[i]);
		}
		i++;
		free(env_name);
	}
        return (NULL);
}



#endif /*HEADER_H */
