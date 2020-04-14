#include <stdlib.h>
#include <stdio.h>
/**
* alloc_grid - function
* Description: a function that concatenates two strings
* @width: integer value of width
* @height: integer value of height
* Return: 2-D array of integers
*/
char **alloc_grid(int width, int height)
{
	int **grid;
	int i, j, k;

	/*checking if width and height are negative or zero*/
	if (width <= 0 || height <= 0)
	{
		return (NULL);
	}
	/*memory allocation in height*/
	grid = malloc(height * sizeof(int *));
	/*check if malloc on grid failed in height direction*/
	if (grid == NULL)
	{
		return (NULL);
	}
	/*memory allocation in width*/
	for (i = 0; i < height; i++)
	{
		grid[i] = malloc(width * sizeof(int));
		/*check if malloc on grid failed in width direction*/
		if (grid[i] == NULL)
		{
			for (k = 0; k <= i; k++)
			{
				free(grid[k]);
			}
			free(grid);
			return (NULL);
		}
	}
	/*initialize every elements in grid to 0 */
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			grid[i][j] = 0;
		}
	}
	return (grid);
}
/**
 * print_grid - prints a grid of integers
 * @grid: the address of the two dimensional grid
 * @width: width of the grid
 * @height: height of the grid
 *
 * Return: Nothing.
 */
void print_grid(int **grid, int width, int height)
{
    int w;
    int h;

    h = 0;
    while (h < height)
    {
        w = 0;
        while (w < width)
        {
            printf("%d ", grid[h][w]);
            w++;
        }
        printf("\n");
        h++;
    }   
}
/**
* free_grid - function
* Description: a function that frees 2-D array
* @grid: 2-D integer pointer
* @height: number of rows
* Return: nothing
*/
void free_grid(int **grid, int height)
{
	int i;

	for (i = 0; i < height; i++)
	{
		free(grid[i]);
	}
	free(grid);
}
/**
 * main - check the code for Holberton School students.
 *
 * Return: Always 0.
 */
int main(void)
{
    int **grid;

    grid = alloc_grid(6, 4);
    if (grid == NULL)
    {
        return (1);
    }
    print_grid(grid, 6, 4);
    printf("\n");
    grid[0][3] = 98;
    grid[3][4] = 402;
    print_grid(grid, 6, 4);
    free_grid(grid, 4);
    return (0);
}
