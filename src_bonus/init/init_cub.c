/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:32:57 by alde-abr          #+#    #+#             */
/*   Updated: 2026/03/02 20:32:58 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include "libft.h"
#include "mlx_utils.h"
#include <fcntl.h>
#include <math.h>

#define ERR_FILE "Error: Invalid file name\n"

static void	init_config(t_cub *cub)
{
	cub->config.fov = M_PI / 3;
	cub->config.tile_size = 1.0;
	cub->config.dist_proj = (WIN_WIDTH / 2) / tan(cub->config.fov / 2);
	cub->config.mouse_sensitivity = 0.02f;
	cub->config.move_speed = 20.0f;
	cub->config.rot_speed = 10.0f;
	cub->config.collision_margin = 0.2f;
	cub->config.update_fps_interval = 500;
	cub->config.update_dtime_interval = 1000;
	cub->config.fps_x = WIN_WIDTH - 50;
	cub->config.fps_y = 250;
}

/**
 * @brief Initialize cub structure, map, player and window.
 * @return 0 on success, 1 on init error
 */
int	cub_init(t_cub *cub, char *map_name)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd < 0 || check_extension(map_name, ".cub"))
		return (printf(ERR_FILE), 1);
	ft_memset(cub, 0, sizeof(t_cub));
	if (get_map(fd, &cub->map) || check_textures(&cub->map))
		return (free_map(&cub->libx, &cub->map), close(fd), 1);
	close(fd);
	init_player(&cub->map, &cub->player);
	if (init_window(cub))
		return (free_map(&cub->libx, &cub->map), close(fd), 1);
	if (load_textures(&cub->libx, &cub->map))
		return (free_map(&cub->libx, &cub->map), close(fd), 1);
	init_config(cub);
	return (0);
}
