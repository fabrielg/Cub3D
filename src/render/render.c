/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:32:48 by alde-abr          #+#    #+#             */
/*   Updated: 2026/03/02 20:32:49 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx_utils.h"

/**
 * @brief Draw the textured wall slice between y_start and y_end.
 */
static void	draw_wall_slice(t_libx *libx, t_texture *txt, int x, t_column *col)
{
	float	step;
	float	tex_pos;
	int		tex_y;
	int		color;
	int		y;

	step = (float)(txt->size) / (float)col->wall_height;
	tex_pos = (col->y_start - WIN_HEIGHT / 2 + col->wall_height / 2) * step;
	y = col->y_start;
	while (y <= col->y_end)
	{
		tex_y = (int)tex_pos % txt->size;
		tex_pos += step;
		color = get_texture_pixel(txt, col->texture_x, tex_y);
		put_pixel(&libx->game_img, x, y, color);
		y++;
	}
}

/**
 * @brief Draw a textured wall column with ceiling and floor.
 */
void	draw_column(t_libx *libx, t_map *map, int x, t_column *col)
{
	t_texture	texture;

	draw_vertical_line(&libx->game_img, x, (int [2]){0, col->y_start - 1},
		map->colors[0]);
	texture = map->textures[col->raycast.hit_side];
	draw_wall_slice(libx, &texture, x, col);
	draw_vertical_line(&libx->game_img, x,
		(int [2]){col->y_end + 1, WIN_HEIGHT - 1}, map->colors[1]);
}

/**
 * @brief Update 3D scene by casting rays per column.
 */
void	update_frame(t_cub *cub)
{
	t_column	col;
	t_player	*p;
	t_map		*map;
	int			x;

	p = &cub->player;
	map = &cub->map;
	x = 0;
	while (x < WIN_WIDTH)
	{
		col.angle = get_ray_angle(p, x, cub->config.fov);
		col.raycast = get_wall_distance(&cub->map, p, col.angle);
		col.texture_x = get_texture_x(&col.raycast, p->position, map);
		col.raycast.distance *= cosf(col.angle - p->angle_view);
		get_wall_slice(&col, col.raycast.distance, &cub->config);
		draw_column(&cub->libx, map, x, &col);
		x++;
	}
}

/**
 * @brief Render full frame with minimap and FPS.
 */
void	render_frame(t_cub *cub)
{
	t_libx	*libx;

	libx = &cub->libx;
	update_frame(cub);
	mlx_put_image_to_window(libx->mlx, libx->window,
		libx->game_img.img, 0, 0);
}
