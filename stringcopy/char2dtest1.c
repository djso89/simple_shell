#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main ()
{
	char *line = "ls -l /usr";
	char *temp_line = NULL;
	char *word, *temp_word;
	char **av;
	int ac = 0;;
	int av_count = 0;
	//size_t n = 16;
	//ssize_t num_read;

	//printf("#cisfun$ ");
	//num_read = getline(&line, &n, stdin);
	//line[num_read - 1] = '\0';
	temp_line = malloc(sizeof(char) * (strlen(line) + 1));
	temp_line = strdup(line);
	printf("%s\n", temp_line);
	if (temp_line == NULL)
	{
		//free(line);
		return (1);
	}

	//printf("Bytes read: %li\n",(long int) num_read);

	temp_word = strtok(temp_line, " ");
	while(temp_word)
	{
		ac++;
		temp_word = strtok(NULL, " ");
	}
	free(temp_line);

	av = malloc(sizeof(char *) * (ac + 1));
	if (av == NULL)
	{
		free(line);
		return (1);
	}
	printf("here\n");
	free(temp_line);
	
	temp_line = malloc(sizeof(char) * (strlen(line) + 1));
	temp_line = strdup(line);

	word = strtok(temp_line, " ");
	while (word)
	{
		printf("%s\n", word);
		av[av_count] = word;
		word = strtok(NULL, " ");
		av_count++;
	}
	av[av_count] = NULL;
	printf("here\n");
	//free(temp_line);
	for (int i = 0; av[i] != NULL; i++)
	{
		printf("av[%d]: %s\n",i ,av[i]);
	}
	free(temp_line);
	free(av[0]);
	free(av);
        //free(line);

	return (0);
}
