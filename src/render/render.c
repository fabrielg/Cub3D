#include "cub3d.h"
#include "libft.h"
#include <math.h>
#include <mlx.h>
#include <stdio.h>

#define COLOR_WALL		0x808080

#define FOV			M_PI / 3
#define TILE_SIZE	1.0
#define DIST_PROJ	(WIN_WIDTH / 2) / tan(FOV / 2)

typedef struct s_column
{
	float	angle;
	float	distance;
	int		wall_height;
	int		y_start;
	int		y_end;
}	t_column;

static float	get_ray_angle(t_player *p, int x)
{
	return (p->angle_view - (FOV / 2.0f) + ((float)x * FOV / WIN_WIDTH));
}

static float	get_wall_distance(t_map *map, t_player *p, float angle)
{
	float	distance;

	distance = dda(map->grid, p->position, angle);
	distance *= cosf(angle - p->angle_view);
	return (distance);
}

static void	get_wall_slice(t_column *col, float distance)
{
	col->wall_height = (int)((TILE_SIZE / distance) * DIST_PROJ);
	col->y_start = (WIN_HEIGHT / 2) - (col->wall_height / 2);
	col->y_end = (WIN_HEIGHT / 2) + (col->wall_height / 2);
}

static void	draw_column(t_libx *libx, t_map *map, int x, t_column *col)
{
	draw_vertical_line(&libx->img_data, x, 0, 
		col->y_start - 1, map->colors[0]);
	
	draw_vertical_line(&libx->img_data, x, col->y_start, 
		col->y_end, COLOR_WALL);
	
	draw_vertical_line(&libx->img_data, x, col->y_end + 1, 
		WIN_HEIGHT - 1, map->colors[1]);
}

void	render_frame(t_libx *libx, t_map *map, t_player *p)
{
	t_column	col;
	int			x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		col.angle = get_ray_angle(p, x);
		col.distance = get_wall_distance(map, p, col.angle);
		get_wall_slice(&col, col.distance);
		draw_column(libx, map, x, &col);
		x++;
	}

	mlx_put_image_to_window(libx->mlx, libx->window, 
		libx->img_data.img, 0, 0);
}
