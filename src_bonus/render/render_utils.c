/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:34:30 by alde-abr          #+#    #+#             */
/*   Updated: 2026/03/02 20:37:14 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Get ray angle for given screen column.
 * @return Ray angle in radians
 */
float	get_ray_angle(t_player *p, int x, float fov)
{
	return (p->angle_view - (fov / 2.0f) + ((float)x * fov / WIN_WIDTH));
}

/**
 * @brief Initialize ray direction and delta distances.
 */
void	init_ray_direction(t_ray_data *ray, float angle, float pos[2])
{
	ray->dir_x = cosf(angle);
	ray->dir_y = sinf(angle);
	ray->map_x = (int)pos[0];
	ray->map_y = (int)pos[1];
	if (ray->dir_x == 0)
		ray->delta_dist_x = (float)1e30;
	else
		ray->delta_dist_x = fabsf(1.0f / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = (float)1e30;
	else
		ray->delta_dist_y = fabsf(1.0f / ray->dir_y);
}

/**
 * @brief Cast a ray and return wall distance data.
 * @return Ray data containing hit information
 */
t_ray_data	get_wall_distance(t_map *map, t_player *p, float angle)
{
	t_ray_data	raycast;

	raycast = dda(map->grid, p->position, angle);
	return (raycast);
}

/**
 * @brief Get wall slice height and screen bounds.
 */
void	get_wall_slice(t_column *col, float distance, t_cub_config *conf)
{
	float	tile_size;
	float	dist_proj;

	tile_size = conf->tile_size;
	dist_proj = conf->dist_proj;
	col->wall_height = (int)((tile_size / distance) * dist_proj);
	col->y_start = (WIN_HEIGHT / 2) - (col->wall_height / 2);
	if (col->y_start < 0)
		col->y_start = 0;
	col->y_end = (WIN_HEIGHT / 2) + (col->wall_height / 2);
	if (col->y_end > WIN_HEIGHT)
		col->y_end = WIN_HEIGHT;
}
