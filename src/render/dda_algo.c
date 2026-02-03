#include <math.h>
#include "cub3d.h"

static void	init_ray_direction(t_ray_data *ray, float angle, float pos[2])
{
	// 1. ray distance
	ray->dir_x = cosf(angle);
	ray->dir_y = sinf(angle);

	// 2. current grid player position
	ray->map_x = (int)pos[0];
	ray->map_y = (int)pos[1];

	// 3. deltas : distance to the next line
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30f;
	else
		ray->delta_dist_x = fabsf(1.0f / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30f;
	else
		ray->delta_dist_y = fabsf(1.0f / ray->dir_y);
}

static void	init_ray_step(t_ray_data *ray, float pos[2])
{
	// 4. +1 or -1 steps
	ray->step_x = 1 - (ray->dir_x < 0) * 2;
	ray->step_y = 1 - (ray->dir_y < 0) * 2;

	// 5. first side distance
	if (ray->dir_x < 0)
		ray->side_dist_x = (pos[0] - ray->map_x) * ray->delta_dist_x;
	else
		ray->side_dist_x = (ray->map_x + 1.0f - pos[0]) * ray->delta_dist_x;

	if (ray->dir_y < 0)
		ray->side_dist_y = (pos[1] - ray->map_y) * ray->delta_dist_y;
	else
		ray->side_dist_y = (ray->map_y + 1.0f - pos[1]) * ray->delta_dist_y;
}

// 6. move step by step
static int	perform_dda_loop(t_ray_data *ray, char **grid)
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
			|| !grid[ray->map_y] || !grid[ray->map_y][ray->map_x])
			return (0);
		if (grid[ray->map_y][ray->map_x] == '1')
			return (1);
	}
}

// 7. get distance
static void	get_distance(t_ray_data *ray, float pos[2])
{
	if (ray->side == 0)
		ray->distance = (ray->map_x - pos[0] + (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->distance = (ray->map_y - pos[1] + (1 - ray->step_y) / 2) / ray->dir_y;
}

t_ray_data	dda(char **grid, float p_position[2], float ray_angle)
{
	t_ray_data	ray;

	init_ray_direction(&ray, ray_angle, p_position);
	init_ray_step(&ray, p_position);
	ray.distance = 1000.0f;
	if (perform_dda_loop(&ray, grid))
		get_distance(&ray, p_position);
	return (ray);
}