#include "cub3d.h"
#include "parser.h"
#include "libft.h"
#include "mlx_utils.h"

/**
 * @brief Main game loop updating FPS and rendering.
 * @return Always returns 0
 */
int	game_loop(t_cub *cub)
{
	render_frame(cub);
	return (0);
}

/**
 * @brief Cub3D main
 * @return 0 on normal exit, 1 on error
 */
int	main(int argc, char *argv[])
{
	t_cub	cub;

	if (argc != 2)
		return (1);
	if (cub_init(&cub, argv[1]))
		return (1);
	mlx_loop_hook(cub.libx.mlx, game_loop, &cub);
	mlx_loop(cub.libx.mlx);
	return (0);
}
