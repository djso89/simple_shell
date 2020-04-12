#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

	line[strlen(line) - 1] = '\0';
	ac = num_words(line, ' ');
	//printf("%s\n",line);
	av = malloc(sizeof(char *) * (ac + 1));
	if (av == NULL)
	{
		free(line);
		return (NULL);
	}
	word = strtok(line, " ");
	//printf("%s\n", line);
	while (word)
	{
		av[av_cnt] = word;
		printf("%s\n", av[av_cnt]);
		word = strtok(NULL, " ");
		av_cnt++;
	}
	free(line);
	av[av_cnt] = NULL;
	av_cnt = 0;
	return (av);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	char *line;
	char **av;
	unsigned int i = 0;
	size_t n = 0;

	getline(&line,&n,stdin);
	av = line_to_av(line);
	for (i = 0; av[i]; i++)
	{
		printf("av[%d]: %s\n",i ,av[i]);
	}
	free(av);
	return (0);
}
