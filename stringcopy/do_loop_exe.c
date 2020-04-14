#include "header.h"
void print_av(char **av)
{
	unsigned int i;
	for (i = 0; av[i]; i++)
	{
		printf("line 104: av[%d]: %s\n",i ,av[i]);
	}
}

int main()
{
	char *line = NULL;//= "ls -l /usr";
	char **av;
	size_t rd_cnt = 0;
	ssize_t num_read;
	

	do
	{
		num_read = getline(&line, &rd_cnt,stdin);
		printf("rd_cnt is %ld\n",rd_cnt);
		if (num_read == -1)
		{
			free(line);
			return (1);
		}
		line[num_read - 1] = '\0';
		av = line_to_av(line);
		print_av(av);
		free_av(av);
		//free(line);
		fflush(stdin);
	}while(num_read != -1);
	free(line);
	fflush(stdin);
	fclose(stdin);
	return (0);
}
