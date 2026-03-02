/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:32:39 by alde-abr          #+#    #+#             */
/*   Updated: 2026/03/02 20:32:41 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Set a pixel color in the image buffer.
 */
void	put_pixel(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || WIN_WIDTH < x || y < 0 || WIN_HEIGHT < y)
		return ;
	dst = data->addr
		+ (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief Get pixel color from texture at given coords.
 * @return Texture pixel color or black if out of bounds
 */
int	get_texture_pixel(t_texture *texture, int tex_x, int tex_y)
{
	char	*pixel;

	if (tex_x < 0 || tex_x >= texture->size
		|| tex_y < 0 || tex_y >= texture->size)
		return (0x000000);
	pixel = texture->img_data.addr + (tex_y * texture->img_data.line_length
			+ tex_x * (texture->img_data.bits_per_pixel / 8));
	return (*(int *)pixel);
}

/**
 * @brief Draw a vertical line in the image buffer.
 */
void	draw_vertical_line(t_img_data *img, int x, int y[2], int color)
{
	while (y[0] <= y[1])
	{
		put_pixel(img, x, y[0], color);
		y[0]++;
	}
}

/**
 * @brief Draw a horizontal line in the image buffer.
 */
void	draw_horizontal_line(t_img_data *img, int x[2], int y, int color)
{
	while (x[0] <= x[1])
	{
		put_pixel(img, x[0], y, color);
		x[0]++;
	}
}
