#include "cub3d.h"
#include <math.h>
#include <mlx.h>
#include <stdio.h>

#define COLOR_WALL		0x808080

#define FOV			M_PI / 3
#define TILE_SIZE	1.0
#define DIST_PROJ	(WIN_WIDTH / 2) / tan(FOV / 2)

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
		angle = p->angle_view - (FOV / 2.0f) + ((float)x * FOV / WIN_WIDTH);
		(void)angle;
		distance = 5.0f;
		
		wall_height = (int)((TILE_SIZE / distance) * DIST_PROJ);
		y_start = (WIN_HEIGHT / 2) - (wall_height / 2);
		y_end = (WIN_HEIGHT / 2) + (wall_height / 2);

		draw_vertical_line(&libx->img_data, x, 0, y_start - 1, map->colors[0]);
		
		draw_vertical_line(&libx->img_data, x, y_start, y_end, COLOR_WALL);
	
		draw_vertical_line(&libx->img_data, x, y_end + 1, WIN_HEIGHT - 1, map->colors[1]);

		x++;
	}
	
	mlx_put_image_to_window(libx->mlx, libx->window, libx->img_data.img, 0, 0);
}

/*static float	dda(t_map *map, int side_dist[2], int deltas[2], int map_xy[2], int steps[2])
{
	int	hit = 0;
	int side;

	while (hit == 0)
	{
		if (side_dist[0] < side_dist[1])
		{
			side_dist[0] += deltas[0];
			map_xy[0] += steps[0];
			side = 0;
		}
		else
		{
			side_dist[1] += deltas[1];
			map_xy[1] += steps[1];
			side = 1;
		}

		if (map_xy[0] < 0 || map_xy[1] < 0 || !map->grid[map_xy[0]][map_xy[1]])
    		return (1000.0f);
		
		if (map->grid[map_xy[0]][map_xy[1]] == '1')
			hit = 1;
	}
	
}

float cast_ray(t_map *map, t_player *player, float angle)
{
	const float	ray_dir_x = cos(angle);
	const float	ray_dir_y = sin(angle);

	int	map_xy[2];
	map_xy[0] = (int)player->position[0];
	map_xy[1] = (int)player->position[1];

	int	delta_dist[2];

	delta_dist[0] = INT_MAX;
	if (ray_dir_x != 0)
		delta_dist[0] = abs(1.0 / ray_dir_x);
	delta_dist[1] = INT_MAX;
	if (ray_dir_y != 0)
		delta_dist[1] = abs(1.0 / ray_dir_y);
	
	int	steps[2];
	int	side_dist[2];
	if (ray_dir_x < 0)
	{
		steps[0] = -1;
		side_dist[0] = (player->position[0] - map_x) * delta_dist[0];
	}
	else
	{
		steps[0] = 1;
    	side_dist[0] = (map_x + 1.0 - player->position[0]) * delta_dist[0];
	}

	if (ray_dir_y < 0)
	{
		steps[1] = -1;
		side_dist[1] = (player->position[1] - map_y) * delta_dist[1];
	}
	else
	{
		steps[1] = 1;
    	side_dist[1] = (map_y + 1.0 - player->position[1]) * delta_dist[1];
	}

}*/
