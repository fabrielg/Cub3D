/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:31:54 by alde-abr          #+#    #+#             */
/*   Updated: 2026/03/02 20:31:55 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keycodes.h"
#include "mlx_utils.h"
#include <mlx.h>
#include "libft.h"

/**
 * @brief Handle key press events for movement and actions.
 * @return 0 if handled, 1 if unrecognized key
 */
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
	else
		return (1);
	return (0);
}

/**
 * @brief Register keyboard, mouse, and close window hooks.
 */
void	register_hooks(t_cub *cub)
{
	mlx_hook(cub->libx.window, 17, 0, close_window, cub);
	mlx_hook(cub->libx.window, 2, 1L << 0, key_press, cub);
}
