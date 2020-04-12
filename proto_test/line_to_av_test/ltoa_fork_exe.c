#include "header.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	char *line;
	char **av;
	unsigned int i = 0;
	size_t n = 0;
	ssize_t num_read;
	pid_t child;
	int fork_stat = 0;

	while((num_read = getline(&line,&n,stdin)))
	{
		line[strlen(line) - 1] = '\0';
		av = line_to_av(line);
		for (i = 0; av[i]; i++)
		{
			printf("av[%d]: %s\n",i ,av[i]);
		}
		printf("av[0] is filename: %s\n", av[0]);
  
		av[0] =check_directory(av[0], envp);

		child = fork();
		if (child == 0)
		{
			if (execve(av[0], av, envp) == -1)
			{
				perror("Error");
			}
			return (1);
		}
		else
			wait(&fork_stat);
		free(av);
		free(line);
		fflush(stdin);
	}
	return (0);
}
