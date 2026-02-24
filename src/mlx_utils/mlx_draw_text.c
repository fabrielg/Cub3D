#include "cub3d.h"
#include <mlx.h>
#include <stdlib.h>

// Draw text at given screen position with color
void	draw_text(t_libx *libx, char *str, int x, int y)
{
	if ((x > WIN_WIDTH || x < 0) || (y > WIN_HEIGHT || y < 0))
		return ;
	mlx_string_put(libx->mlx, libx->window, x, y, 0xFFFFFF, str);
}
