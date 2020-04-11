#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
	if (access("/bin/ls", F_OK) == 0)
	{
		printf("file exist\n");
	}
	else
		printf("file does not exist\n");
	return (0);
}
