#include "libft.h"
#include "cub3d.h"

#define VALID_CELLS "NSWE0"
#define SURROUND_ERROR "Error: [x: %i, y:%i] not surrounded (%s)\n"

int	is_valid_cell(char c)
{
	if (ft_strchr(VALID_CELLS, c))
		return (1);
	return (0);
}

int	is_surrounded(char **grid, int *widths, int y, int x)
{
	if (y == 0 || x == 0)
		return (printf(SURROUND_ERROR, x, y, "START"), 0);
	else if (!grid[y + 1] || !grid[y][x + 1])
		return (printf(SURROUND_ERROR, x, y, "END"), 0);
	else if (x >= widths[y - 1] || grid[y - 1][x] == ' ')
		return (printf(SURROUND_ERROR, x, y, "UP"), 0);
	else if (x >= widths[y + 1] || grid[y + 1][x] == ' ')
		return (printf(SURROUND_ERROR, x, y, "DOWN"), 0);
	else if (grid[y][x + 1] == ' ')
		return (printf(SURROUND_ERROR, x, y, "RIGHT"), 0);
	else if (grid[y][x - 1] == ' ')
		return (printf(SURROUND_ERROR, x, y, "LEFT"), 0);
	return (1);
}

int	check_grid(char **grid, int *widths)
{
	int	x;
	int	y;

	y = -1;
	while (grid[++y])
	{
		x = -1;
		while(grid[y][++x])
		{
			if (is_valid_cell(grid[y][x]) && !is_surrounded(grid, widths, y, x))
				return (1);
		}
	}
	return (0);
}
