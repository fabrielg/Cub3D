#include "libft.h"
#include "map.h"

static void	debug_texture(t_map *map)
{
	int	i;

	i = -1;
	write(1, "//Texture//\n", 12);
	while (++i < 4)
	{
		if (map->textures[i])
			ft_printf("[%i] %s\n", i, map->textures[i]);
	}
}

static void	debug_color(t_map *map)
{
	int	i;

	i = -1;
	write(1, "//Color//\n", 10);
	while (++i < 2)
	{
		ft_printf("[%i] %i\n", i, map->colors[i]);
	}
}

static void	debug_grid(t_map *map)
{
	int	i;

	i = -1;
	write(1, "//Grid//\n", 9);
	while(++i  < map->max_height)
		printf("%3i.(%3i) | %s\n", i, map->widths[i], map->grid[i]);
}

void	debug_map(t_map *map)
{
	write(1, "\n===DEBUG MAP===\n\n", 18);
	debug_texture(map);
	write(1, "\n", 1);
	debug_color(map);
	write(1, "\n", 1);
	debug_grid(map);
}

