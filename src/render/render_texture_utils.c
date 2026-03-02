#include "cub3d.h"

/**
 * @brief Get horizontal texture coordinate for wall.
 * @return Texture x coordinate
 */
int	get_texture_x(t_ray_data *raycast, float pos[2], t_map *map)
{
	t_texture	texture;
	float		wall_x_hit;
	int			texture_x;

	if (raycast->side == 0)
		wall_x_hit = pos[1] + raycast->distance * raycast->dir_y;
	else
		wall_x_hit = pos[0] + raycast->distance * raycast->dir_x;
	wall_x_hit -= floorf(wall_x_hit);
	texture = map->textures[raycast->hit_side];
	texture_x = (int)(wall_x_hit * texture.size);
	if ((raycast->side == 0 && raycast->dir_x > 0)
		|| (raycast->side == 1 && raycast->dir_y < 0))
		texture_x = texture.size - texture_x - 1;
	return (texture_x);
}
