#include "kshell.h"
/**
 * num_words - this function takes lines and counts number of words
 * @line: string line from the input
 * Return: Word counts
 */
unsigned int num_words(char *line)
{
	int fldelim = 0;
	unsigned int wc = 0;

	while (*line)
	{
		if (*line == ' ')
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
* _strlen - function
* Description: swaps the values of two integers
* @s: char pointer
* Return: number of characters
*/
int _strlen(char *s)
{
	int numchars;

	numchars = 0;
	while (*(s + numchars) != '\0')
	{
		numchars++;
	}
	return (numchars);
}
/**
* _strncpy - function
* Description: copy source char pointer to dest char up to n characters
* @dest: target char pointer
* @src: source char pointer
* @n: n of characters in src up to n
* Return: char pointer
*/
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	i = 0;
	while (i < n && *(src + i))
	{
		*(dest + i) = *(src + i);
		i++;
	}
	while (i < n)
	{
		*(dest + i) = '\0';
		i++;
	}
	return (dest);
}
/**
* _strcmp - function
* Description: compare the two string
* @s1: target char pointer
* @s2: another char pointer to compare
* Return: 0 if s1 s2 are same; if not same, then return ascii diff of s1 and s2
*/
int _strcmp(char *s1, char *s2)
{
	/*run the loop as long as s1 is not \0*/
	while (*s1)
	{
		/*when s1 and s2 are not same, then break out of loop*/
		if (*s1 != *s2)
		{
			break;
		}
		/*increment the pointer to move on to next element*/
		s1++;
		s2++;
	}
	/*return the ascii difference*/
	return (*s1 - *s2);
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

	line[_strlen(line) - 1] = '\0';
	ac = num_words(line);
	av = malloc(sizeof(char *) * (ac + 1));
	if (av == NULL)
	{
		free(line);
		return (NULL);
	}
	word = strtok(line, " ");
	while (word)
	{
		av[av_cnt] = malloc(_strlen(word) + 1);
		if (av[av_cnt] == NULL)
		{
			free_av(av);
			return (NULL);
			}
		_strncpy(av[av_cnt], word, _strlen(word) + 1);
		word = strtok(NULL, " ");
		av_cnt++;
	}
	av[av_cnt] = NULL;
	av_cnt = 0;
	return (av);
}
