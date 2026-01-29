#include "cub3d.h"
#include "libft.h"
#include <math.h>
#include <mlx.h>
#include <stdio.h>

#define COLOR_WALL		0x808080

#define FOV			M_PI / 3
#define TILE_SIZE	1.0
#define DIST_PROJ	(WIN_WIDTH / 2) / tan(FOV / 2)

static float	dda(char **grid, float p_position[2], float ray_angle);

void	render_frame(t_libx *libx, t_map *map, t_player *p)
{
	int		x;
	float	angle;
	float	distance;
	int		wall_height;
	int		y_start;
	int		y_end;

	x = 0;
	while (x < WIN_WIDTH)
	{
		// 1. get ray angle
		angle = p->angle_view - (FOV / 2.0f) + ((float)x * FOV / WIN_WIDTH);

		// 2. cast ray with dda to get the distance
		distance = dda(map->grid, p->position, angle);
		distance *= cosf(angle - p->angle_view);

		// 3. get wall height
		wall_height = (int)((TILE_SIZE / distance) * DIST_PROJ);

		// 4. draw vertical lines (ceiling, wall, floor)
		y_start = (WIN_HEIGHT / 2) - (wall_height / 2);
		y_end = (WIN_HEIGHT / 2) + (wall_height / 2);

		draw_vertical_line(&libx->img_data, x, 0, y_start - 1, map->colors[0]);
		
		draw_vertical_line(&libx->img_data, x, y_start, y_end, COLOR_WALL);
	
		draw_vertical_line(&libx->img_data, x, y_end + 1, WIN_HEIGHT - 1, map->colors[1]);

		x++;
	}
	
	mlx_put_image_to_window(libx->mlx, libx->window, libx->img_data.img, 0, 0);
}

static float	absf(float n)
{
	return (n * ((n >= 0.0f) * 2.0f - 1.0f));
}

static float	dda(char **grid, float p_position[2], float ray_angle)
{
	// 1. ray distance
	float	ray_dir_x = cosf(ray_angle);
	float	ray_dir_y = sinf(ray_angle);

	// 2. current grid player position
	int	p_grid_position_x = (int)p_position[0];
	int	p_grid_position_y = (int)p_position[1];

	// 3. deltas : distance to the next line
	float	delta_dist_x;
	float	delta_dist_y;

	if (ray_dir_x == 0)
		delta_dist_x = 1e30f;
	else
		delta_dist_x = absf(1.0f / ray_dir_x);
	if (ray_dir_y == 0)
		delta_dist_y = 1e30f;
	else
		delta_dist_y = absf(1.0f / ray_dir_y);

	// 4. +1 or -1 steps
	int step_x = 1 - (ray_dir_x < 0) * 2;
	int step_y = 1 - (ray_dir_y < 0) * 2;

	// 5. first side distance
	float	side_dist_x;
	if (ray_dir_x < 0)
		side_dist_x = (p_position[0] - p_grid_position_x) * delta_dist_x;
	else
		side_dist_x = (p_grid_position_x + 1.0f - p_position[0]) * delta_dist_x;

	float	side_dist_y;
	if (ray_dir_y < 0)
		side_dist_y = (p_position[1] - p_grid_position_y) * delta_dist_y;
	else
		side_dist_y = (p_grid_position_y + 1.0f - p_position[1]) * delta_dist_y;
	
	// 6. move step by step
	int	side = 0;
	while (1)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			p_grid_position_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			p_grid_position_y += step_y;
			side = 1;
		}

		if (p_grid_position_y < 0 || p_grid_position_x < 0
			|| !grid[p_grid_position_y]
			|| !grid[p_grid_position_y][p_grid_position_x])
			return (1000.0f);

		if (grid[p_grid_position_y][p_grid_position_x] == '1')
			break ;
	}
	
	// 7. get distance
	float	distance;
	if (side == 0)
		distance = (p_grid_position_x - p_position[0] + (1 - step_x) / 2) / ray_dir_x;
	else
		distance = (p_grid_position_y - p_position[1] + (1 - step_y) / 2) / ray_dir_y;
	return (distance);
}
