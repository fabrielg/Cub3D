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
			return (close(fd), 1);
		}
		close(fd);
	}
	return (0);
}

static int	get_texture_data(t_libx *libx, t_texture *texture, char *raw)
{
	int	width;
	int	height;

	texture->img_data.img = mlx_xpm_file_to_image(
		libx->mlx, raw, &width, &height);
	if (!texture->img_data.img || width != height
			|| width <= 0 || height <= 0)
		return (1);
	texture->img_data.addr = mlx_get_data_addr(
		texture->img_data.img,
		&texture->img_data.bits_per_pixel,
		&texture->img_data.line_length,
		&texture->img_data.endian
		);
		texture->size = width;
	return (0);
}

int	load_textures(t_libx *libx, t_map *map)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (get_texture_data(libx, &map->textures[i], map->raw_textures[i]))
			return (1);
	}
	i = -1;
	while (++i < 3)
	{
		if (get_texture_data(libx, &map->door.frames[i],
			map->door.raw_door_texture[i]))
			return (1);
	}
	return (0);
}
