#include "cub3d.h"
#include "keycodes.h"
#include "mlx_utils.h"
#include <mlx.h>

static int	key_press(int k, t_cub *cub)
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

static int	mouse_move_handler(int x, int y, t_cub *cub)
{
	static int	prev_x = WIN_WIDTH / 2;

	(void)y;
	if (x == prev_x)
		return (0);
	if (0 <= x || x <= WIN_WIDTH)
		mlx_mouse_move(cub->libx.mlx, cub->libx.window, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	if (x < prev_x)
		rotate_left(cub);
	else if (x > prev_x)
		rotate_right(cub);
	prev_x = x;
	render_frame(&cub->libx, &cub->map, &cub->player);
	return (0);
}

void	register_hooks(t_cub *cub)
{
	mlx_hook(cub->libx.window, 17, 0, close_window, cub);
	mlx_hook(cub->libx.window, 2, 1L<<0, key_press, cub);
	mlx_hook(cub->libx.window, 6, 1L<<6, mouse_move_handler, cub);
}
