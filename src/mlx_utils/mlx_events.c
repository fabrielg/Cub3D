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
	else if (k == KEY_W)
		move_forward(cub);
	else if (k == KEY_A)
		move_left(cub);
	else if (k == KEY_S)
		move_backward(cub);
	else if (k == KEY_D)
		move_right(cub);
	else if (k == KEY_LEFT)
		rotate_left(cub);
	else if (k == KEY_RIGHT)
		rotate_right(cub);
	else if (k == KEY_R)
		respawn(cub);
	else
		return (1);
	render_frame(&cub->libx, &cub->map, &cub->player);
	return (0);
}
