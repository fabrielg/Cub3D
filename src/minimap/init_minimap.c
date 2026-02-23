#include "cub3d.h"
#include "libft.h"
#include "mlx_utils.h"


//MINIMAP SIZE FUNC //TODO

void	init_minimap(t_libx *libx)
{
	libx->minimap_img.img = mlx_new_image(
			libx->mlx,
			MINIMAP_SIZE,
			MINIMAP_SIZE);
	libx->minimap_img.addr = mlx_get_data_addr(
			&libx->minimap_img.img,
			&libx->minimap_img.bits_per_pixel,
			&libx->minimap_img.line_length,
			&libx->minimap_img.endian);
}
