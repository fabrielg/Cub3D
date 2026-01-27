#include "cub3d.h"
#include "keycodes.h"
#include "mlx_utils.h"
#include <mlx.h>

void	register_hooks(t_cub *cub)
{
	mlx_hook(cub->libx.window, 17, 0, close_window, cub);
	mlx_hook(cub->libx.window, 2, 1L<<0, key_press, cub);
}

int	key_press(int k, t_cub *cub)
{
	if (k == KEY_ESC)
		close_window(cub);
	else
		return (1);
	return (0);
}