#include "cub3d.h"
#include "parser.h"
#include "libft.h"
#include "mlx_utils.h"
#include <fcntl.h>

#define ERR_FILE "Error: Invalid file name\n"

/**
 * @brief Initialize MLX, window, image buffer and hooks.
 */
static void	init_window(t_cub *cub)
{
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
		return (free_map(&cub->map), close(fd), 1);
	close(fd);
	init_player(&cub->map, &cub->player);
	init_window(cub);
	return (load_textures(&cub->libx, &cub->map));
}
