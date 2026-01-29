#include <mlx.h>
#include "cub3d.h"
#include "libft.h"
#include "mlx_utils.h"

static void	force_load_map(t_map *map)
{
	map->textures[0] = "./path_to_the_north_texture";
	map->textures[1] = "./path_to_the_south_texture";
	map->textures[2] = "./path_to_the_west_texture";
	map->textures[3] = "./path_to_the_east_texture";

	map->colors[0] = 0x90DAFC;
	map->colors[1] = 0x4D3F30;

	map->default_position[0] = 5;
	map->default_position[1] = 6;

	map->default_direction = NORTH;

	map->grid = malloc(sizeof(char *) * 11);
	map->grid[0] = "11111111111";
	map->grid[1] = "10000000001";
	map->grid[2] = "10000000001";
	map->grid[3] = "10001110001";
	map->grid[4] = "10000000001";
	map->grid[5] = "11000000001";
	map->grid[6] = "10000N00001";
	map->grid[7] = "10000000001";
	map->grid[8] = "10000000111";
	map->grid[9] = "10001000001";
	map->grid[10] = "11111111111";
}

int	cub_init(t_cub *cub)
{
	ft_memset(cub, 0, sizeof(t_cub));

	force_load_map(&cub->map);
	init_player(&cub->map, &cub->player);

	cub->libx.mlx = mlx_init();
	cub->libx.window = mlx_new_window(
			cub->libx.mlx,
			WIN_WIDTH,
			WIN_HEIGHT,
			WIN_TITLE);
	cub->libx.img_data.img = mlx_new_image(
			cub->libx.mlx,
			WIN_WIDTH,
			WIN_HEIGHT);
	cub->libx.img_data.addr = mlx_get_data_addr(
			cub->libx.img_data.img,
			&cub->libx.img_data.bits_per_pixel,
			&cub->libx.img_data.line_length,
			&cub->libx.img_data.endian);
	mlx_put_image_to_window(
			cub->libx.mlx,
			cub->libx.window,
			cub->libx.img_data.img,
			0, 0);
	register_hooks(cub);
	mlx_mouse_hide(cub->libx.mlx, cub->libx.window);
	return (0);
}

int	main(void)
{
	t_cub	cub;

	cub_init(&cub);
	render_frame(&cub.libx, &cub.map, &cub.player);
	mlx_loop(cub.libx.mlx);
}