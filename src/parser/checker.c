#include "libft.h"
#include "map.h"
#include <math.h>
#include <fcntl.h>

int	check_textures(t_map_data *map)
{
	int	i;
	int	fd;

	i = -1;
	while (++i < 4)
	{
		fd = open(map->textures[i], O_RDONLY);
		if (fd == -1)
		{
			printf("Error: invalid texture file [%s]\n", map->textures[i]);
			return (1);
		}
	}
	return (0);
}

// int	check_map(t_map_data *map)
// {
// 	while (map->grid[])
// }
