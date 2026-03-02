/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:31:51 by alde-abr          #+#    #+#             */
/*   Updated: 2026/03/02 20:31:52 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
