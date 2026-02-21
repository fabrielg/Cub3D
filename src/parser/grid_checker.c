#include "libft.h"
#include "cub3d.h"

#define DIR_CELLS "NSWE"
#define ERR_MULT_PLAYER "Error: [x: %i, y:%i] can't be more than one player\n"
#define ERR_MISS_PLAYER "Error: missing player in grid\n"

#define VALID_CELLS "NSWE0"
#define ERR_SURROUND "Error: [x: %i, y:%i] not surrounded (%s)\n"

/**
 * @brief Check if a character is a valid map cell type.
 * @return 1 if valid cell, 0 otherwise
 */
int	is_valid_cell(char c)
{
	if (ft_strchr(VALID_CELLS, c))
		return (1);
	return (0);
}

/**
 * @brief Validate player cell and ensure only one exists.
 * @return 1 if duplicate player, 0 otherwise
 */
int	check_player_repetition(char *player_out, char c)
{
	if (!ft_strchr(DIR_CELLS, c))
		return (0);
	if (*player_out)
		return (1);
	*player_out = c;
	return (0);
}

/**
 * @brief Check that a cell is properly surrounded by walls.
 * @return 1 if surrounded, 0 if open or invalid
 */
int	is_surrounded(char **grid, int *widths, int y, int x)
{
	if (y == 0 || x == 0)
		return (printf(ERR_SURROUND, x, y, "START"), 0);
	else if (!grid[y + 1] || !grid[y][x + 1])
		return (printf(ERR_SURROUND, x, y, "END"), 0);
	else if (x >= widths[y - 1] || grid[y - 1][x] == ' ')
		return (printf(ERR_SURROUND, x, y, "UP"), 0);
	else if (x >= widths[y + 1] || grid[y + 1][x] == ' ')
		return (printf(ERR_SURROUND, x, y, "DOWN"), 0);
	else if (grid[y][x + 1] == ' ')
		return (printf(ERR_SURROUND, x, y, "RIGHT"), 0);
	else if (grid[y][x - 1] == ' ')
		return (printf(ERR_SURROUND, x, y, "LEFT"), 0);
	return (1);
}

/**
 * @brief Validate the grid and ensure a single player exists.
 * @return 0 if valid grid, 1 on error
 */
int	check_grid(char **grid, int *widths)
{
	int		x;
	int		y;
	char	player;

	player = '\0';
	y = -1;
	while (grid[++y])
	{
		x = -1;
		while (grid[y][++x])
		{
			if (check_player_repetition(&player, grid[y][x]))
				return (printf(ERR_MULT_PLAYER, x, y), 1);
			if (is_valid_cell(grid[y][x]) && !is_surrounded(grid, widths, y, x))
				return (1);
		}
	}
	if (!player)
		return (printf(ERR_MISS_PLAYER), 1);
	return (0);
}
