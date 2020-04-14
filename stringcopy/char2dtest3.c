#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * num_words - this function takes lines and counts number of words
 * @line: string line from the input
 * Return: Word counts
 
unsigned int num_words(char *line, char *delim)
{
	unsigned int wc = 0;
	char *line_cp;
	char *word;
	line_cp = malloc(sizeof(char) +(strlen(line) +1));
	line_cp = strcpy(line_cp,line);
	if (line_cp == NULL)
		return (0);
	word = strtok(line_cp, delim);
	while(word)
	{
		word = strtok(NULL, delim);
		wc++;
	}
        free(line_cp);
	return (wc);
}
**/

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

int main()
{
	char *line = NULL;//= "ls -l /usr";
	size_t rd_cnt = 0;
	ssize_t num_read;
	char **av;
        unsigned int wcnt;
	unsigned int i;
	unsigned int j;
	char *line_cp;
	char *word;

	num_read = getline(&line, &rd_cnt,stdin);
	
		line[num_read - 1] = '\0';
		wcnt = 0;
		wcnt = num_words(line, ' ');
		printf("number of words: %u\n", wcnt);
		
		
		av = malloc(sizeof(char *) * (wcnt + 1));
		if (!av)
		{
			free(line);
			return (1);
		}
		line_cp = strdup(line);
		if (!line_cp)
			return (1);

		word = strtok(line_cp, " ");
		printf("word at first: %s\n", word);
		i = 0;
		j = 0;
		while (word)
		{
			av[i] = strdup(word);
			if (av[i] == NULL)
			{
				for (j = 0; j <= i; j++)
				{
					free(av[j]);
				}
				free(av);
				return (1);
			}
			word = strtok(NULL, " ");
			printf("line 96: word: %s\n", word);
			i++;
		}
	        free(line_cp);
		av[i] = NULL;
		i = 0;
		for (i = 0; av[i]; i++)
		{
			printf("line 104: av[%d]: %s\n",i ,av[i]);
		}
/*free av*/
		for (i = 0; av[i]; i++)
		{
			free(av[i]);
		}
		free(av);
		
		free(line);
		//fflush(stdin);
	
	return (0);
}
