#include "cub3d.h"
#include "libft.h"
#include <mlx.h>

#define MAX_FRAMES 5000

static char	*get_texture_path(int i)
{
	static char	*textures[8] = {
		"textures/cat_animation/cat_0.xpm",
		"textures/cat_animation/cat_1.xpm",
		"textures/cat_animation/cat_2.xpm",
		"textures/cat_animation/cat_3.xpm",
		"textures/cat_animation/cat_4.xpm",
		"textures/cat_animation/cat_5.xpm",
		"textures/cat_animation/cat_6.xpm",
		"textures/cat_animation/cat_7.xpm"
	};

	if (i < 0 || i > 7)
		return (NULL);
	return (textures[i]);
}

int	init_sprite(t_libx *libx, t_map *map)
{
	int	i;
	int	width;
	int	height;

	i = -1;
	while (++i < 8)
	{
		map->sprite_textures[i].img_data.img = mlx_xpm_file_to_image(
				libx->mlx,
				get_texture_path(i),
				&width,
				&height
				);
		if (!map->sprite_textures[i].img_data.img || width != height
			|| width <= 0 || height <= 0)
			return (1);
		map->sprite_textures[i].img_data.addr = mlx_get_data_addr(
				map->sprite_textures[i].img_data.img,
				&map->sprite_textures[i].img_data.bits_per_pixel,
				&map->sprite_textures[i].img_data.line_length,
				&map->sprite_textures[i].img_data.endian
				);
		map->sprite_textures[i].size = width;
	}
	return (0);
}

int	get_sprite_texture_x(t_ray_data *raycast, float p_pos[2], int sprite_size)
{
	float	wall_x;
	int		texture_x;

	if (raycast->side == 0)
		wall_x = p_pos[1] + raycast->distance * raycast->dir_y;
	else
		wall_x = p_pos[0] + raycast->distance * raycast->dir_x;
	wall_x -= floorf(wall_x);
	texture_x = (int)(wall_x * sprite_size);
	if (texture_x < 0)
		texture_x = 0;
	if (texture_x >= sprite_size)
		texture_x = sprite_size - 1;
	return (texture_x);
}

void	update_frame(t_cub *cub)
{
	cub->sprite.sprite_frame_counter++;
	if (cub->sprite.sprite_frame_counter >= MAX_FRAMES)
	{
		cub->sprite.sprite_frame_counter = 0;
		cub->sprite.sprite_id = (cub->sprite.sprite_id + 1) % 8;
		render_frame(cub);
	}
}
