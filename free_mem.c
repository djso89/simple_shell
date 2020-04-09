#include "kshell.h"
/**
 * free_av - clear the cmds 2-D array
 * @cmds: argument value vectors
 * Return: nothing
 */
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
