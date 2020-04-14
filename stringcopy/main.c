#include <stdio.h>
char *_strcpy(char *dest, char *src)
{
	int i;
	int numchar;

	numchar = 0;
	i = 0;

	while (*(src + numchar))
	{
		numchar++;
	}
	while (i <= numchar)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	return (dest);
}

/**
 * main - check the code for Holberton School students.
 *
 * Return: Always 0.
 */
int main(void)
{
    char s1[98];
    char *p;
    p = _strcpy(s1, "First, solve the problem. Then, write the code\n");
    printf("%s", s1);
    printf("%s", p);
    return (0);
}
