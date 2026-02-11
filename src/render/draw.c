#include "cub3d.h"

void	put_pixel(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || WIN_WIDTH < x || y < 0 || WIN_HEIGHT < y)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

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

void	draw_vertical_line(t_img_data *img, int x, int y_start, int y_end, int color)
{
	while (y_start <= y_end)
	{
		put_pixel(img, x, y_start, color);
		y_start++;
	}
}