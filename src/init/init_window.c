/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:31:43 by alde-abr          #+#    #+#             */
/*   Updated: 2026/03/02 20:31:44 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx_utils.h"

/**
 * @brief Initialize the main game image buffer.
 */
static void	init_game_img(t_libx *libx)
{
	libx->game_img.img = mlx_new_image(
			libx->mlx,
			WIN_WIDTH,
			WIN_HEIGHT);
	libx->game_img.addr = mlx_get_data_addr(
			libx->game_img.img,
			&libx->game_img.bits_per_pixel,
			&libx->game_img.line_length,
			&libx->game_img.endian);
}

/**
 * @brief Initialize MLX, window, image buffers and hooks.
 */
int	init_window(t_cub *cub)
{
	cub->libx.mlx = mlx_init();
	if (cub->libx.mlx == NULL)
		return (1);
	cub->libx.window = mlx_new_window(
			cub->libx.mlx,
			WIN_WIDTH,
			WIN_HEIGHT,
			WIN_TITLE);
	init_game_img(&cub->libx);
	register_hooks(cub);
	return (0);
}
