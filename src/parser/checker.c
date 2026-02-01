#include "libft.h"
#include "cub3d.h"
#include <fcntl.h>

int	check_textures(t_map *map)
{
	int	i;
	int	fd;

	i = -1;
	return (0); //TODO
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
