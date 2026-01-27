#include <mlx.h>
#include "cub3d.h"
#include "libft.h"

int	cub_init(t_cub *cub)
{
	ft_memset(cub, 0, sizeof(t_cub));
	cub->libx.mlx = mlx_init();
	cub->libx.window = mlx_new_window(cub->libx.mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	cub->libx.img_data.img = mlx_new_image(cub->libx.mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->libx.img_data.addr = mlx_get_data_addr(cub->libx.img_data.img,
			&cub->libx.img_data.bits_per_pixel,
			&cub->libx.img_data.line_length,
			&cub->libx.img_data.endian);
	mlx_put_image_to_window(cub->libx.mlx, cub->libx.window, cub->libx.img_data.img, 0, 0);
	return (0);
}

static void	mlx_clear(t_libx *libx)
{
	if (!libx->mlx)
		return ;
	if (libx->window)
		mlx_destroy_window(libx->mlx, libx->window);
	mlx_destroy_display(libx->mlx);
	if (libx->mlx)
		free(libx->mlx);
}

int	close_window(t_cub *cub)
{
	if (!cub)
		return (exit(0), 0);
	if (cub->libx.img_data.img)
		mlx_destroy_image(cub->libx.mlx, cub->libx.img_data.img);
	mlx_clear(&cub->libx);
	exit(0);
	return (1);
}

int	main(void)
{
	t_cub	cub;

	cub_init(&cub);
	mlx_loop(cub.libx.mlx);
}