#include "cub3d.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>

#define MOVE_SPEED			20.0f
#define ROT_SPEED			10.0f
#define COLLISION_MARGIN	0.2f

static int	check_collision(t_map *map, float x, float y)
{
	char	up_l;
	char	up_r;
	char	dw_l;
	char	dw_r;

	up_l = map->grid[(int)(y - COLLISION_MARGIN)][(int)(x - COLLISION_MARGIN)];
	up_r = map->grid[(int)(y - COLLISION_MARGIN)][(int)(x + COLLISION_MARGIN)];
	dw_l = map->grid[(int)(y + COLLISION_MARGIN)][(int)(x - COLLISION_MARGIN)];
	dw_r = map->grid[(int)(y + COLLISION_MARGIN)][(int)(x + COLLISION_MARGIN)];
	if (ft_strchr("1C", up_l) || ft_strchr("1C", up_r) ||ft_strchr("1C", dw_l)
		|| ft_strchr("1C", dw_r))
		return (1);
	return (0);
}

/**
 * @brief Move player in a specified direction vector with collision check.
 */
int	move_player(t_cub *cub, float dir_x, float dir_y)
{
	float	new_x = cub->player.position[0] + dir_x * MOVE_SPEED * cub->fps.delta_time;
	float	new_y = cub->player.position[1] + dir_y * MOVE_SPEED * cub->fps.delta_time;

	if (check_collision(&cub->map, new_x, new_y) == 0)
	{
		cub->player.position[0] = new_x;
		cub->player.position[1] = new_y;
	}
	return 0;
}

/**
 * @brief Rotate player by a given angle delta.
 */
int	rotate_player(t_cub *cub, float delta)
{
	cub->player.angle_view += delta * ROT_SPEED * cub->fps.delta_time;
	cub->player.angle_view = fmodf(cub->player.angle_view, 2 * M_PI);
	if (cub->player.angle_view < 0)
		cub->player.angle_view += 2 * M_PI;
	return 0;
}

static void	close_doors(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->max_height)
	{
		while(map->grid[i][j])
		{
			if (map->grid[i][j] == 'O')
				map->grid[i][j] = 'C';
			j++;
		}
		j = 0;
		i++;
	}
}

int	respawn(t_cub *cub)
{
	cub->player.position[0] = cub->map.default_position[0];
	cub->player.position[1] = cub->map.default_position[1];
	cub->player.angle_view = get_cardinal_angle(cub->map.default_direction);
	close_doors(&cub->map);
	return (0);
}
