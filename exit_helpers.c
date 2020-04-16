#include "kshell.h"
/**
 * get_exit_stat - function that takes the status value from wait
 * and returns the exit number
 * @stat: stat number obtained from wait
 * Return: error number
 */

int get_exit_stat(int stat)
{
	if (stat == 256)
	{
		return (1);
	}
	if (stat == 512)
		return (2);
	else
		return (0);
}
