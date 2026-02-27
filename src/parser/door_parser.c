#include "cub3d.h"
#include "libft.h"
#include "parser.h"
#include <fcntl.h>

#define DOOR_TEXTURE "textures/cobblestone.xpm"

#define ERR_TXTR_EXTENSION "Error: Texture \"%s\" need [.xpm] extension\n"
#define ERR_TEXTURE "Error: invalid texture file \"%s\"\n"

static int check_door_texture(char *fd_name)
{
	int	fd;

	fd = open(fd_name, O_RDONLY);
	if (fd == -1)
	{
		printf(ERR_TEXTURE, fd_name);
		return (close(fd), 1);
	}
	return (close(fd), 0);
}

int	parse_door(t_map *map)
{
	if (!DOOR_TEXTURE || !DOOR_TEXTURE[0])
		return (1);
	if (check_extension(DOOR_TEXTURE, ".xpm"))
		return (printf(ERR_TXTR_EXTENSION, DOOR_TEXTURE), 1);
	map->raw_door_texture = ft_strdup(DOOR_TEXTURE);
	if (!map->raw_door_texture || check_door_texture(map->raw_door_texture))
		return (1);
	return (0);
}
