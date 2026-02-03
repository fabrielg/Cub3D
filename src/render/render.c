#include "cub3d.h"
#include "libft.h"
#include <math.h>
#include <mlx.h>
#include <stdio.h>

#define COLOR_WALL		0x808080
#define FOV				M_PI / 3
#define TILE_SIZE		1.0
#define TEXTURE_WIDTH	64
#define TEXTURE_HEIGHT	64
#define DIST_PROJ		(WIN_WIDTH / 2) / tan(FOV / 2)

static float	get_ray_angle(t_player *p, int x)
{
	return (p->angle_view - (FOV / 2.0f) + ((float)x * FOV / WIN_WIDTH));
}

static t_ray_data	get_wall_distance(t_map *map, t_player *p, float angle)
{
	t_ray_data	raycast;

	raycast = dda(map->grid, p->position, angle);
	return (raycast);
}

static void	get_wall_slice(t_column *col, float distance)
{
	col->wall_height = (int)((TILE_SIZE / distance) * DIST_PROJ);
	col->y_start = (WIN_HEIGHT / 2) - (col->wall_height / 2);
	col->y_end = (WIN_HEIGHT / 2) + (col->wall_height / 2);
}

static void	draw_column(t_libx *libx, t_map *map, int x, t_column *col)
{
	t_img_data	*texture;
	float		step;
	float		tex_pos;
	int			tex_y;
	int			color;
	int			y;

	draw_vertical_line(&libx->img_data, x, 0, 
		col->y_start - 1, map->colors[0]);
	
	texture = &map->textures[col->raycast.hit_side];
	step = (float)TEXTURE_HEIGHT / (float)col->wall_height;
	tex_pos = (col->y_start - WIN_HEIGHT / 2 + col->wall_height / 2) * step;
	
	y = col->y_start;
	while (y <= col->y_end)
	{
		tex_y = (int)tex_pos % TEXTURE_HEIGHT;
		tex_pos += step;
		
		color = get_texture_pixel(texture, col->texture_x, tex_y);
		put_pixel(&libx->img_data, x, y, color);
		
		y++;
	}
	
	draw_vertical_line(&libx->img_data, x, col->y_end + 1, 
		WIN_HEIGHT - 1, map->colors[1]);
}

static int	get_texture_x(t_ray_data *raycast, float pos[2])
{
	float	wall_x_hit;
	int		texture_x;

	if (raycast->side == 0)
		wall_x_hit = pos[1] + raycast->distance * raycast->dir_y;
	else
		wall_x_hit = pos[0] + raycast->distance * raycast->dir_x;
	wall_x_hit -= floorf(wall_x_hit);

	texture_x = (int)(wall_x_hit * TEXTURE_WIDTH);

	if ((raycast->side == 0 && raycast->dir_x > 0) 
		|| (raycast->side == 1 && raycast->dir_y < 0))
		texture_x = TEXTURE_WIDTH - texture_x - 1;
	return (texture_x);
}

void	render_frame(t_libx *libx, t_map *map, t_player *p)
{
	t_column	col;
	int			x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		col.angle = get_ray_angle(p, x);
		col.raycast = get_wall_distance(map, p, col.angle);
		col.texture_x = get_texture_x(&col.raycast, p->position);
		col.raycast.distance *= cosf(col.angle - p->angle_view);
		get_wall_slice(&col, col.raycast.distance);
		draw_column(libx, map, x, &col);
		x++;
	}

	mlx_put_image_to_window(libx->mlx, libx->window, 
		libx->img_data.img, 0, 0);
}
