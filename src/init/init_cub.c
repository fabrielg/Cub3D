#include "cub3d.h"
#include "parser.h"
#include "libft.h"
#include "mlx_utils.h"
#include <fcntl.h>

#define ERR_FILE "Error: Invalid file name\n"

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
		return (free_map(&cub->libx, &cub->map), close(fd), 1);
	close(fd);
	init_player(&cub->map, &cub->player);
	init_window(cub);
	if (load_textures(&cub->libx, &cub->map))
		return (free_map(&cub->libx, &cub->map), close(fd), 1);
	return (0);
}
