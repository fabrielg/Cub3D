#include "libft.h"
#include "cub3d.h"
#include "mlx_utils.h"
#include <fcntl.h>

#define ERR_TEXTURE "Error: invalid texture file \"%s\"\n"

int	check_textures(t_map *map)
{
	int	i;
	int	fd;

	i = -1;
	while (++i < 4)
	{
		fd = open(map->raw_textures[i], O_RDONLY);
		if (fd == -1)
		{
			printf(ERR_TEXTURE, map->raw_textures[i]);
			return (1);
		}
	}
	return (0);
}

int	load_textures(t_libx *libx, t_map *map)
{
	int	i;
	int	width;
	int	height;

	i = -1;
	while (++i < 4)
	{
		map->textures[i].img_data.img = mlx_xpm_file_to_image(
				libx->mlx,
				map->raw_textures[i],
				&width,
				&height
				);
		if (!map->textures[i].img_data.img || width != height
			|| width <= 0 || height <= 0)
			return (1);
		map->textures[i].img_data.addr = mlx_get_data_addr(
				map->textures[i].img_data.img,
				&map->textures[i].img_data.bits_per_pixel,
				&map->textures[i].img_data.line_length,
				&map->textures[i].img_data.endian
				);
		map->textures[i].size = width;
	}
	return (0);
}
