#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char *str= "ls -l /usr";
	char *str_cpy = NULL;
	str_cpy = malloc(sizeof(char) *(strlen(str) + 1));
	str_cpy = strncpy(str_cpy, str, strlen(str) + 1);

	printf("%s\n", str_cpy);

	free(str_cpy);
	
	return (0);
}
