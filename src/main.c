#include <fcntl.h>
#include "cub3d.h"
#include "parser.h"
#include "libft.h"
#include "mlx_utils.h"

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
