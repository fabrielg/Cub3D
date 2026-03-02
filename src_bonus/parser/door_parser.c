/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:33:38 by alde-abr          #+#    #+#             */
/*   Updated: 2026/03/02 20:33:39 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "parser.h"
#include <fcntl.h>

#define DOOR_ANIM_1 "textures/door/door_anim1.xpm"
#define DOOR_ANIM_2 "textures/door/door_anim2.xpm"
#define DOOR_ANIM_3 "textures/door/door_anim3.xpm"

#define DOOR_FRAME_DURATION 0.1f

#define ERR_TXTR_EXTENSION "Error: Texture \"%s\" need [.xpm] extension\n"
#define ERR_TEXTURE "Error: invalid texture file \"%s\"\n"

/**
 * @brief Check if door texture file can be opened.
 * @return 0 if valid, 1 on open error
 */
static int	check_door_texture(char *fd_name)
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

/**
 * @brief Validate door texture path and duplicate it.
 * @return Duplicated path or NULL on error
 */
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

/**
 * @brief Get door animation textures path into map.
 * @return 0 on success, 1 on failure
 */
int	parse_door(t_map *map)
{
	map->door.raw_door_texture[0] = get_raw_door(DOOR_ANIM_1);
	map->door.raw_door_texture[1] = get_raw_door(DOOR_ANIM_2);
	map->door.raw_door_texture[2] = get_raw_door(DOOR_ANIM_3);
	if (!map->door.raw_door_texture[0] || !map->door.raw_door_texture[1]
		|| !map->door.raw_door_texture[2])
		return (1);
	map->door.frame_duration = DOOR_FRAME_DURATION;
	return (0);
}
