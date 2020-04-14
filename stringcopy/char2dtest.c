#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * num_words - this function takes lines and counts number of words
 * @line: string line from the input
 * Return: Word counts
 */
unsigned int num_words(char *line, char delim)
{
	int fldelim = 0;
	unsigned int wc = 0;
	unsigned int i; 
	i = 0;
	while (line[i])
	{
		if (line[i] == delim)
			fldelim = 0;
		else if (fldelim == 0)
		{
			fldelim = 1;
			wc++;
		}
		++i;
	}
	return (wc);
}


int main()
{
	char *line= "ls -l /usr";
	char *word;
	char **av;
	int ac = 0;
	int av_cnt = 0;
	char *line_cpy;
	line_cpy = malloc(sizeof(char) * (strlen(line) + 1));
	if (!line_cpy)
		return (1);
	line_cpy = strdup(line);
	ac = num_words(line, ' ');
	printf("%s\n",line_cpy);
	av = malloc(sizeof(char *) * (ac + 1));
	if (av == NULL)
	{
		free(line_cpy);
		return (1);
	}
	word = strtok(line_cpy, " ");
	//printf("%s\n", line);
	while (word)
	{
		av[av_cnt] = word;
		word = strtok(NULL, " ");
		av_cnt++;
	}
        for (int i = 0; i< av_cnt; i++)
	{
		printf("av[%d]: %s\n", i,av[i]);
	}
	free(line);
	//free(line_cpy);
	//free(av[av_cnt]);
	free(av[0]);
	free(av);
	//free(av[0]);
	return (0);
}
