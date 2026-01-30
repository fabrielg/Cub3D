#include "cub3d.h"
#include <math.h>

float	get_cardinal_angle(t_direction direction)
{
	static const float	angles[4] = {
		3.0f * M_PI_2,
		M_PI_2,
		0.0f,
		M_PI
	};

	return (angles[direction]);
}

static void	init_player_direction(t_map *map, t_player *player)
{
	player->angle_view = get_cardinal_angle(map->default_direction);
}

static void	init_player_position(t_map *map, t_player *player)
{
	player->position[0] = map->default_position[0] + 0.5f;
	player->position[1] = map->default_position[1] + 0.5f;
}

void	init_player(t_map *map, t_player *player)
{
	init_player_position(map, player);
	init_player_direction(map, player);
}