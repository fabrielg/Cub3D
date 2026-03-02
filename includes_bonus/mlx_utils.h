/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:31:19 by alde-abr          #+#    #+#             */
/*   Updated: 2026/03/02 20:31:20 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "cub3d.h"
# include <mlx.h>

/* Utils */

void	mlx_clear(t_libx *libx);
int		close_window(t_cub *cub);
void	draw_text(t_libx *libx, char *str, int x, int y);

/* Events */

void	register_hooks(t_cub *cub);

#endif
