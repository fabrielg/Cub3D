#include "cub3d.h"
#include <mlx.h>
#include <stdlib.h>

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

static void	textures_clear(void *mlx_ptr, t_texture textures[4])
{
	int	i;

	if (!mlx_ptr)
		return ;
	i = -1;
	while (++i < 4)
		if (textures[i].img_data.img)
			mlx_destroy_image(mlx_ptr, textures[i].img_data.img);
}

void	cub_clear(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub->libx.img_data.img)
		mlx_destroy_image(cub->libx.mlx, cub->libx.img_data.img);
	textures_clear(cub->libx.mlx, cub->map.textures);
	mlx_clear(&cub->libx);
}

int	close_window(t_cub *cub)
{
	if (!cub)
		return (exit(0), 0);
	cub_clear(cub);
	exit(0);
	return (1);
}