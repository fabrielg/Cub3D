#include "cub3d.h"
#include <mlx.h>

static void	draw_column(t_libx *libx, t_map *map, int x, t_column *col)
{
	t_texture	texture;
	float		step;
	float		tex_pos;
	int			tex_y;
	int			color;
	int			y;

	draw_vertical_line(&libx->img_data, x, 0, 
		col->y_start - 1, map->colors[0]);
	
	texture = map->textures[col->raycast.hit_side];
	step = (float)(texture.size) / (float)col->wall_height;
	tex_pos = (col->y_start - WIN_HEIGHT / 2 + col->wall_height / 2) * step;
	
	y = col->y_start;
	while (y <= col->y_end)
	{
		tex_y = (int)tex_pos % texture.size;
		tex_pos += step;
		
		color = get_texture_pixel(&texture, col->texture_x, tex_y);
		put_pixel(&libx->img_data, x, y, color);
		
		y++;
	}
	
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
		col.raycast = get_wall_distance(map, p, col.angle);
		col.texture_x = get_texture_x(&col.raycast, p->position, map->textures);
		col.raycast.distance *= cosf(col.angle - p->angle_view);
		get_wall_slice(&col, col.raycast.distance);
		draw_column(libx, map, x, &col);
		x++;
	}

	mlx_put_image_to_window(libx->mlx, libx->window, 
		libx->img_data.img, 0, 0);
}
