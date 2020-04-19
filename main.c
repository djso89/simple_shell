#include "kshell.h"
char *convert(long int num, int base);
/**
 * main - Entry Point
 * @argc: number of argument count.
 * @argv: array of argument strings
 * @env: environment array of strings
 * Return: 0 (Success)
 */
int main(int argc, char **argv, char **env)
{
	char *line = NULL, *filename, **av;
	size_t n;
	ssize_t num_read;
	int exit_status = 0;
	int spc_flag = 0, cmd_num = 0;
	(void)argc;
	/*(void)argv;*/

	check_prompt();
	while ((num_read = getline(&line, &n, stdin)) != EOF)
	{
		cmd_num++;
		/*printf("line is %s\n", line);*/
		spc_flag = check_spc_nl(line);
		if (spc_flag == 1)
		{
			spc_flag = 0;
			check_prompt();
			continue;
		}
		line[num_read - 1] = '\0';
		av = line_to_av(line);
		filename = check_input(av[0], env);
		if (filename == NULL)
		{
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ":", 1);
			write(STDERR_FILENO, " ", 1);
			write(STDERR_FILENO, convert(cmd_num, 10), _strlen(convert(cmd_num, 10)));
			write(STDERR_FILENO, ":", 1);
			write(STDERR_FILENO, " ", 1);
			write(STDERR_FILENO, av[0], _strlen(av[0]));
			write(STDERR_FILENO, ": not found\n", 12);
			exit_status = 127;
		}
		else
		{
			exit_status = 0;
			free(av[0]);
			/*printf("filename is %s\n", filename);*/
			av[0] = _strdup(filename);
			execute(av, env, argv[0]);
		}
		free(filename);
		free_av(av);
		check_prompt();
	}
	check_EOF(num_read);
	free(line);
	return (exit_status);
}
/**
 * convert - converter function, a clone of itoa
 * @num: number
 * @base: base
 *
 * Return: string
 */
char *convert(long int num, int base)
{
	static char *array = "0123456789abcdef";
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (num < 0)
	{
		n = -num;
		sign = '-';
	}
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
