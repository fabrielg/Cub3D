#include "cub3d.h"
#include "libft.h"
#include "keycodes.h"
#include "mlx_utils.h"
#include <mlx.h>

// Draws a filled rectangle between two corners
void	draw_square(t_img_data *img, int x, int y, int size, int color)
{
	int		tmp;

	tmp = x;
	while (tmp <= (x + size))
	{
		draw_vertical_line(img, tmp, y, y + size, color);
		tmp++;
	}
}
