#include "header1.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	size_t n = 0;
	ssize_t num_read;
	char **av;
	char *line;

	while((num_read = getline(&line,&n,stdin)))
	{
		line[strlen(line) - 1] = '\0';
		av = line_to_av(line);

		if ((strcmp(av[0], "exit") == 0))
		{
			free(av);
			free(line);
			fflush(stdin);
			exit(EXIT_SUCCESS);
		}

		free(av);
		free(line);
		fflush(stdin);
	}
	return (0);
}
