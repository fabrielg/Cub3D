#include "libft.h"
#include "cub3d.h"

void	free_textures(t_map *map)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (!map->raw_textures[i])
			continue ;
		free(map->raw_textures[i]);
		map->raw_textures[i] = NULL;
	}
}

void	free_grid(t_map *map)
{
	int	i;

	i = -1;
	if (map->grid)
	{
		while(map->grid[++i])
		{
			free(map->grid[i]);
			map->grid[i] = NULL;
		}
		free(map->grid);
		map->grid = NULL;
	}
}

void	free_widths(t_map *map)
{
	if (map->widths)
	{
		free(map->widths);
		map->widths = NULL;
	}
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	free_textures(map);
	free_grid(map);
	free_widths(map);
}
