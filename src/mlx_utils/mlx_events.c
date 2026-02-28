#include "cub3d.h"
#include "keycodes.h"
#include "mlx_utils.h"
#include <mlx.h>
#include "libft.h"

#define MOUSE_SENSITIVITY 0.02f

static int	key_press(int k, t_cub *cub)
{
	float	angle;

	angle = cub->player.angle_view;
	if (k == KEY_ESC)
		close_window(cub);
	else if (k == KEY_W)
		move_player(cub, cosf(angle), sinf(angle));
	else if (k == KEY_S)
		move_player(cub, -cosf(angle), -sinf(angle));
	else if (k == KEY_A)
		move_player(cub, cosf(angle - M_PI_2), sinf(angle - M_PI_2));
	else if (k == KEY_D)
		move_player(cub, cosf(angle + M_PI_2), sinf(angle + M_PI_2));
	else if (k == KEY_LEFT)
		rotate_player(cub, -1.0f);
	else if (k == KEY_RIGHT)
		rotate_player(cub, 1.0f);
	else if (k == KEY_R)
		respawn(cub);
	else if (k == KEY_E)
		open_door(cub);
	else
		return (1);
	render_frame(cub);
	return (0);
}

static int	mouse_move_handler(int x, int y, t_cub *cub)
{
	static int	prev_x = WIN_WIDTH / 2;
	int			delta_x;

	(void)y;
	if (x == prev_x)
		return (0);
	delta_x = (int)((x - prev_x) * MOUSE_SENSITIVITY);
	if (ft_abs(delta_x) < 1)
		return (0);
	rotate_player(cub, delta_x);
	if (x < (WIN_WIDTH / 2) - 20 || x > (WIN_WIDTH / 2) + 20)
	{
		mlx_mouse_move(cub->libx.mlx, cub->libx.window,
			WIN_WIDTH / 2, WIN_HEIGHT / 2);
		prev_x = WIN_WIDTH / 2;
	}
	else
		prev_x = x;
	render_frame(cub);
	return (0);
}

void	register_hooks(t_cub *cub)
{
	mlx_hook(cub->libx.window, 17, 0, close_window, cub);
	mlx_hook(cub->libx.window, 2, 1L<<0, key_press, cub);
	mlx_hook(cub->libx.window, 6, 1L<<6, mouse_move_handler, cub);
}
