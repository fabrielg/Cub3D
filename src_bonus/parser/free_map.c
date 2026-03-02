/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:33:42 by alde-abr          #+#    #+#             */
/*   Updated: 2026/03/02 20:33:43 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"
#include <mlx.h>

/**
 * @brief Free all raw texture paths and texture img stored in the map structure.
 */
static void	free_textures(t_libx *libx, t_map *map)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (map->raw_textures[i])
		{
			free(map->raw_textures[i]);
			map->raw_textures[i] = NULL;
		}
		if (map->textures[i].img_data.img)
			mlx_destroy_image(libx->mlx, map->textures[i].img_data.img);
	}
	i = -1;
	while (++i < 3)
	{
		if (map->door.raw_door_texture[i])
		{
			free(map->door.raw_door_texture[i]);
			map->door.raw_door_texture[i] = NULL;
		}
		if (map->door.frames[i].img_data.img)
			mlx_destroy_image(libx->mlx, map->door.frames[i].img_data.img);
	}
}

/**
 * @brief Free the 2D grid array and reset its pointers to NULL.
 */
static void	free_grid(t_map *map)
{
	int	i;

	i = -1;
	if (map->grid)
	{
		while (map->grid[++i])
		{
			free(map->grid[i]);
			map->grid[i] = NULL;
		}
		free(map->grid);
		map->grid = NULL;
	}
}

/**
 * @brief Free the widths array and reset the pointer to NULL.
 */
static void	free_widths(t_map *map)
{
	if (map->widths)
	{
		free(map->widths);
		map->widths = NULL;
	}
}

/**
 * @brief Free all allocated resources inside the map structure.
 */
void	free_map(t_libx *libx, t_map *map)
{
	if (!map)
		return ;
	free_textures(libx, map);
	free_grid(map);
	free_widths(map);
}
