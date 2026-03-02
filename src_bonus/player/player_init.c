/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:34:13 by alde-abr          #+#    #+#             */
/*   Updated: 2026/03/02 20:34:14 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <math.h>

/**
 * @brief Convert cardinal direction to corresponding angle in radians.
 * @return Angle in radians for the given direction
 */
float	get_cardinal_angle(t_direction direction)
{
	static const float	angles[4] = {
		3.0f * M_PI_2,
		M_PI_2,
		0.0f,
		M_PI
	};

	return (angles[direction]);
}

/**
 * @brief Find player start position and return initial direction.
 * @return Direction index corresponding to starting orientation
 */
static t_direction	init_player_position(t_map *map, t_player *player)
{
	const char	*dir = "NSEW";
	char		*res;
	int			x;
	int			y;

	y = 0;
	res = NULL;
	while (y < map->max_height)
	{
		x = 0;
		while (x < map->widths[y])
		{
			res = ft_strchr(dir, map->grid[y][x]);
			if (res)
			{
				player->position[0] = x + 0.5f;
				player->position[1] = y + 0.5f;
				return (res - dir);
			}
			x++;
		}
		y++;
	}
	return (NORTH);
}

/**
 * @brief Initialize player position, default position and angle view.
 */
void	init_player(t_map *map, t_player *player)
{
	map->default_direction = init_player_position(map, player);
	map->default_position[0] = player->position[0];
	map->default_position[1] = player->position[1];
	player->angle_view = get_cardinal_angle(map->default_direction);
}
