#include "libft.h"
#include "cub3d.h"

static void	debug_texture(t_map *map)
{
	int	i;

	i = -1;
	printf("//Texture//\n");
	while (++i < 4)
	{
		if (map->raw_textures[i])
			printf("[%i] %s\n", i, map->raw_textures[i]);
	}
}

static void	debug_color(t_map *map)
{
	int	i;

	i = -1;
	printf("//Color//\n");
	while (++i < 2)
	{
		printf("[%i] %i\n", i, map->colors[i]);
	}
}

static void	debug_grid(t_map *map)
{
	int	i;

	i = -1;
	printf("//Grid//\n");
	while(++i  < map->max_height)
		printf("%3i.(%3i) | %s\n", i, map->widths[i], map->grid[i]);
}

void	debug_map(t_map *map)
{
	printf("\n===DEBUG MAP===\n\n");
	debug_texture(map);
	printf("\n");
	debug_color(map);
	printf("\n");
	debug_grid(map);
}

