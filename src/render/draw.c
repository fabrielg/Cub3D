#include "cub3d.h"

static void	put_pixel(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || WIN_WIDTH < x || y < 0 || WIN_HEIGHT < y)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_vertical_line(t_img_data *img, int x, int y_start, int y_end, int color)
{
	while (y_start <= y_end)
	{
		put_pixel(img, x, y_start, color);
		y_start++;
	}
}