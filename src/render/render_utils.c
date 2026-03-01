#include "cub3d.h"
#include "stdio.h"

float	get_ray_angle(t_player *p, int x)
{
	return (p->angle_view - (FOV / 2.0f) + ((float)x * FOV / WIN_WIDTH));
}

/*
1. ray distance
2. current grid player position
3. deltas : distance to the next line
*/
void	init_ray_direction(t_ray_data *ray, float angle, float pos[2])
{
	ray->dir_x = cosf(angle);
	ray->dir_y = sinf(angle);
	ray->map_x = (int)pos[0];
	ray->map_y = (int)pos[1];
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30f;
	else
		ray->delta_dist_x = fabsf(1.0f / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30f;
	else
		ray->delta_dist_y = fabsf(1.0f / ray->dir_y);
}

t_ray_data	get_wall_distance(t_map *map, t_player *p, float angle)
{
	t_ray_data	raycast;

	raycast = dda(map->grid, p->position, angle);
	return (raycast);
}

void	get_wall_slice(t_column *col, float distance)
{
	col->wall_height = (int)((TILE_SIZE / distance) * DIST_PROJ);
	col->y_start = (WIN_HEIGHT / 2) - (col->wall_height / 2);
	if (col->y_start < 0)
		col->y_start = 0;
	col->y_end = (WIN_HEIGHT / 2) + (col->wall_height / 2);
	if (col->y_end > WIN_HEIGHT)
		col->y_end = WIN_HEIGHT;
}

t_texture	select_texture(t_ray_data *raycast, t_map *map)
{
	if (raycast->tile_type == 'C')
		return (map->door.frames[map->door.current_frame]);
	return (map->textures[raycast->hit_side]);
}

int	get_texture_x(t_ray_data *raycast, float pos[2], t_map *map)
{
	t_texture	texture;
	float		wall_x_hit;
	int			texture_x;

	if (raycast->side == 0)
		wall_x_hit = pos[1] + raycast->distance * raycast->dir_y;
	else
		wall_x_hit = pos[0] + raycast->distance * raycast->dir_x;
	wall_x_hit -= floorf(wall_x_hit);
	texture = select_texture(raycast, map);
	texture_x = (int)(wall_x_hit * texture.size);
	if ((raycast->side == 0 && raycast->dir_x > 0)
		|| (raycast->side == 1 && raycast->dir_y < 0))
		texture_x = texture.size - texture_x - 1;
	return (texture_x);
}
