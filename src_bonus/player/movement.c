/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:34:09 by alde-abr          #+#    #+#             */
/*   Updated: 2026/03/02 20:34:10 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>

/**
 * @brief Check for collision at a given position with walls or doors.
 * @return 1 if collision detected, 0 otherwise
 */
static int	check_collision(t_map *map, float x, float y, float margin)
{
	char	up_l;
	char	up_r;
	char	dw_l;
	char	dw_r;

	up_l = map->grid[(int)(y - margin)][(int)(x - margin)];
	up_r = map->grid[(int)(y - margin)][(int)(x + margin)];
	dw_l = map->grid[(int)(y + margin)][(int)(x - margin)];
	dw_r = map->grid[(int)(y + margin)][(int)(x + margin)];
	if (ft_strchr("1C", up_l) || ft_strchr("1C", up_r) || ft_strchr("1C", dw_l)
		|| ft_strchr("1C", dw_r))
		return (1);
	return (0);
}

/**
 * @brief Move player in a specified direction vector with collision check.
 */
int	move_player(t_cub *cub, float dir_x, float dir_y)
{
	float	new_x;
	float	new_y;

	new_x = cub->player.position[0]
		+ dir_x * cub->config.move_speed * cub->fps.delta_time;
	new_y = cub->player.position[1]
		+ dir_y * cub->config.move_speed * cub->fps.delta_time;
	if (check_collision(&cub->map, new_x, new_y, cub->config.collision_margin))
		return (1);
	cub->player.position[0] = new_x;
	cub->player.position[1] = new_y;
	return (0);
}

/**
 * @brief Rotate player by a given angle delta.
 */
int	rotate_player(t_cub *cub, float delta)
{
	cub->player.angle_view += delta
		* cub->config.rot_speed * cub->fps.delta_time;
	cub->player.angle_view = fmodf(cub->player.angle_view, 2 * M_PI);
	if (cub->player.angle_view < 0)
		cub->player.angle_view += 2 * M_PI;
	return (0);
}

/**
 * @brief Close all open doors in the map.
 */
static void	close_doors(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->max_height)
	{
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'O')
				map->grid[i][j] = 'C';
			j++;
		}
		j = 0;
		i++;
	}
}

/**
 * @brief Reset player to default position and close all doors.
 * @return Always returns 0
 */
void	respawn(t_cub *cub)
{
	cub->player.position[0] = cub->map.default_position[0];
	cub->player.position[1] = cub->map.default_position[1];
	cub->player.angle_view = get_cardinal_angle(cub->map.default_direction);
	close_doors(&cub->map);
}
