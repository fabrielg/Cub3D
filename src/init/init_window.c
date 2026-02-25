#include "cub3d.h"
#include "libft.h"
#include "mlx_utils.h"
#include "minimap.h"

/**
 * @brief Return the smaller value between two integers.
 * @return The lower of the two values
 */
static int	get_lower(int n1, int n2)
{
	if (n1 < n2)
		return (n1);
	return (n2);
}

/**
 * @brief Initialize the minimap image and buffer.
 */
static void	init_minimap_img(t_libx *libx)
{
	libx->minimap_size = get_lower(WIN_HEIGHT, WIN_WIDTH) / MINIMAP_SCALE;
	libx->minimap_img.img = mlx_new_image(
			libx->mlx,
			libx->minimap_size,
			libx->minimap_size);
	libx->minimap_img.addr = mlx_get_data_addr(
			libx->minimap_img.img,
			&libx->minimap_img.bits_per_pixel,
			&libx->minimap_img.line_length,
			&libx->minimap_img.endian);
}

/**
 * @brief Initialize the main game image buffer.
 */
static void	init_game_img(t_libx *libx)
{
	libx->game_img.img = mlx_new_image(
			libx->mlx,
			WIN_WIDTH,
			WIN_HEIGHT);
	libx->game_img.addr = mlx_get_data_addr(
			libx->game_img.img,
			&libx->game_img.bits_per_pixel,
			&libx->game_img.line_length,
			&libx->game_img.endian);
}

/**
 * @brief Initialize MLX, window, image buffers and hooks.
 */
void	init_window(t_cub *cub)
{
	cub->libx.mlx = mlx_init();
	cub->libx.window = mlx_new_window(
			cub->libx.mlx,
			WIN_WIDTH,
			WIN_HEIGHT,
			WIN_TITLE);
	init_game_img(&cub->libx);
	init_minimap_img(&cub->libx);
	register_hooks(cub);
}
