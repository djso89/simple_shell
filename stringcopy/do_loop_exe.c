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
		printf("line 96: word: %s\n", word);
		i++;
	}
	/*strtok and duplicate end*/
	free(line_cp);
	av[i] = NULL;
	return (av);
}


int main()
{
	char *line = NULL;//= "ls -l /usr";
	char **av;
	size_t rd_cnt = 0;
	ssize_t num_read;
	unsigned int i;

	do
	{
		num_read = getline(&line, &rd_cnt,stdin);
		if (num_read == -1)
		{
			free(line);
			return (1);
		}
		line[num_read - 1] = '\0';
		av = line_to_av(line);
		for (i = 0; av[i]; i++)
		{
			printf("line 104: av[%d]: %s\n",i ,av[i]);
		}
		free_av(av);
		//free(line);
		fflush(stdin);
	}while(num_read != -1);
	//free_av(av);
	free(line);
	//fclose(stdin);
	fflush(stdin);
	return (0);
}
