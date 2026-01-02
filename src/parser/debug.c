#include "libft.h"
#include "map.h"

static void	debug_texture(t_map_data *map)
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

static void	debug_color(t_map_data *map)
{
	int	i;

	i = -1;
	write(1, "//Color//\n", 10);
	while (++i < 2)
	{
		ft_printf("[%i] %i\n", i, map->colors[i]);
	}
}

void	debug_map(t_map_data *map)
{
	write(1, "===DEBUG MAP===\n\n", 17);
	debug_texture(map);
	write(1, "\n", 1);
	debug_color(map);
}

