#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "cub3d.h"

/* Utils */
void	mlx_clear(t_libx *libx);
int		close_window(t_cub *cub);

/* Events */
void	register_hooks(t_cub *cub);
int		key_press(int k, t_cub *cub);

#endif