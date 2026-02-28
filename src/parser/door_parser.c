#include "cub3d.h"
#include "libft.h"
#include "parser.h"
#include <fcntl.h>

#define DOOR_ANIM_1 "textures/door/door_anim1.xpm"
#define DOOR_ANIM_2 "textures/door/door_anim2.xpm"
#define DOOR_ANIM_3 "textures/door/door_anim3.xpm"

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

char	*get_raw_door(char *str)
{
	if (!str || !str[0])
		return (NULL);
	if (check_extension(str, ".xpm"))
		return (printf(ERR_TXTR_EXTENSION, str), NULL);
	if (check_door_texture(str))
		return (NULL);
	return (ft_strdup(str));
}

int	parse_door(t_map *map)
{
	map->door.raw_door_texture[0] = get_raw_door(DOOR_ANIM_1);
	map->door.raw_door_texture[1] = get_raw_door(DOOR_ANIM_2);
	map->door.raw_door_texture[2] = get_raw_door(DOOR_ANIM_3);
	if (!map->door.raw_door_texture[0] || !map->door.raw_door_texture[1]
		|| !map->door.raw_door_texture[2])
		return (1);
	return (0);
}
