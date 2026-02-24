#include "cub3d.h"
#include <math.h>
#include <stdio.h>

#define MOVE_SPEED			100.0f
#define ROT_SPEED			50.f
#define COLLISION_MARGIN	0.2f

static int	check_collision(t_map *map, float x, float y)
{
	if (map->grid[(int)(y - COLLISION_MARGIN)][(int)(x - COLLISION_MARGIN)] == '1')
		return (1);
	if (map->grid[(int)(y - COLLISION_MARGIN)][(int)(x + COLLISION_MARGIN)] == '1')
		return (1);
	if (map->grid[(int)(y + COLLISION_MARGIN)][(int)(x - COLLISION_MARGIN)] == '1')
		return (1);
	if (map->grid[(int)(y + COLLISION_MARGIN)][(int)(x + COLLISION_MARGIN)] == '1')
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

int	respawn(t_cub *cub)
{
	cub->player.position[0] = cub->map.default_position[0];
	cub->player.position[1] = cub->map.default_position[1];
	cub->player.angle_view = get_cardinal_angle(cub->map.default_direction);
	return (0);
}
