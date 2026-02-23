#include "cub3d.h"
#include "libft.h"
#include "mlx_utils.h"

#define MINIMAP_CELL MINIMAP_SIZE / 5

//MINIMAP SIZE FUNC //TODO

void	init_minimap(t_libx *libx)
{
	libx->minimap_img.img = mlx_new_image(
			libx->mlx,
			MINIMAP_SIZE,
			MINIMAP_SIZE);
	libx->minimap_img.addr = mlx_get_data_addr(
			libx->minimap_img.img,
			&libx->minimap_img.bits_per_pixel,
			&libx->minimap_img.line_length,
			&libx->minimap_img.endian);
}

void	render_minimap(t_libx *libx)
{
	int	x;
	int	y;

	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			draw_square(&libx->minimap_img, x * MINIMAP_CELL, y * MINIMAP_CELL, MINIMAP_CELL, 0xFFFFFF);
			x++;
		}
		y++;
	}
}
