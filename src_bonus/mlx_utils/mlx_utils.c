/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:33:26 by alde-abr          #+#    #+#             */
/*   Updated: 2026/03/02 20:33:27 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include <mlx.h>
#include <stdlib.h>

/**
 * @brief Free MLX resources and destroy the window.
 */
void	mlx_clear(t_libx *libx)
{
	if (!libx->mlx)
		return ;
	if (libx->window)
		mlx_destroy_window(libx->mlx, libx->window);
	mlx_destroy_display(libx->mlx);
	if (libx->mlx)
		free(libx->mlx);
}

/**
 * @brief Close the game window and free all resources.
 * @return 0 on normal exit, 1 if cub pointer is invalid
 */
int	close_window(t_cub *cub)
{
	if (!cub)
		return (exit(0), 0);
	free_map(&cub->libx, &cub->map);
	if (cub->libx.game_img.img)
		mlx_destroy_image(cub->libx.mlx, cub->libx.game_img.img);
	if (cub->libx.minimap_img.img)
		mlx_destroy_image(cub->libx.mlx, cub->libx.minimap_img.img);
	mlx_clear(&cub->libx);
	exit(0);
	return (1);
}
