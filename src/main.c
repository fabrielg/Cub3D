#include <mlx.h>
#include <fcntl.h>
#include "cub3d.h"
#include "parser.h"
#include "libft.h"
#include "mlx_utils.h"

int	cub_init(t_cub *cub, int fd)
{
	ft_memset(cub, 0, sizeof(t_cub));

	if (get_map(fd, &cub->map))
		return (free_map(&cub->map), 1);
	// debug_map(&cub->map);
	check_textures(&cub->map);

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
	return (0);
}

int	main(int argc, char *argv[])
{
	t_cub	cub;
	int		fd;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);

	if (cub_init(&cub, fd))
		return (1);
	render_frame(&cub.libx, &cub.map, &cub.player);
	mlx_loop(cub.libx.mlx);
	return (0);
}
