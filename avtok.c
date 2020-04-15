#include "kshell.h"

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

	line_cp = _strdup(line);
	if (!line_cp)
		return (NULL);
	wcnt = 0; /*start tokenizing and store into av format*/
	wcnt = num_words(line, ' ');
	av = malloc(sizeof(char *) * (wcnt + 1));
	if (!av)
	{
		free(line_cp);
		return (NULL);
	}
	word = strtok(line_cp, " ");
	i = 0;
	j = 0;
	while (word)
	{
		av[i] = _strdup(word);
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
	free(line_cp);
	av[i] = NULL;
	return (av);
}
