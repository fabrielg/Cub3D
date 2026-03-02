/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:32:37 by alde-abr          #+#    #+#             */
/*   Updated: 2026/03/02 20:35:11 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "stdio.h"

/**
 * @brief Initialize ray step direction and first side distances.
 */
static void	init_ray_step(t_ray_data *ray, float pos[2])
{
	ray->step_x = 1 - (ray->dir_x < 0) * 2;
	ray->step_y = 1 - (ray->dir_y < 0) * 2;
	if (ray->dir_x < 0)
		ray->side_dist_x = (pos[0] - ray->map_x) * ray->delta_dist_x;
	else
		ray->side_dist_x = (ray->map_x + 1.0f - pos[0]) * ray->delta_dist_x;
	if (ray->dir_y < 0)
		ray->side_dist_y = (pos[1] - ray->map_y) * ray->delta_dist_y;
	else
		ray->side_dist_y = (ray->map_y + 1.0f - pos[1]) * ray->delta_dist_y;
}

/**
 * @brief Perform DDA loop until wall or door is hit.
 * @return 1 if hit detected, 0 if out of bounds
 */
static int	perform_dda_loop(t_ray_data *ray, t_map *map)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
			ray->hit_side = WEST + ((EAST - WEST) * (ray->step_x > 0));
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
			ray->hit_side = NORTH + ((SOUTH - NORTH) * (ray->step_y > 0));
		}
		if (ray->map_y < 0 || ray->map_x < 0
			|| ray->map_y >= map->max_height
			|| ray->map_x >= map->widths[ray->map_y])
			return (0);
		if (map->grid[ray->map_y][ray->map_x] == '1'
				|| map->grid[ray->map_y][ray->map_x] == 'C')
			return (1);
	}
}

/**
 * @brief Get perpendicular wall distance for ray.
 */
static void	get_distance(t_ray_data *ray, float pos[2])
{
	if (ray->side == 0)
	{
		ray->distance = (ray->map_x - pos[0]
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	}
	else
	{
		ray->distance = (ray->map_y - pos[1]
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	}
}

/**
 * @brief Cast a ray using DDA and return ray data.
 * @return Filled ray data structure
 */
t_ray_data	dda(t_map *map, float p_position[2], float ray_angle)
{
	t_ray_data	ray;

	init_ray_direction(&ray, ray_angle, p_position);
	init_ray_step(&ray, p_position);
	ray.distance = 1000.0f;
	if (perform_dda_loop(&ray, map))
		get_distance(&ray, p_position);
	return (ray);
}
