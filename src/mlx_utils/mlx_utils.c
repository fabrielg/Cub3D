#include "cub3d.h"
#include <mlx.h>
#include <stdlib.h>

void	mlx_clear(t_libx *libx)
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