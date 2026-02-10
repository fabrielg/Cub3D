#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "cub3d.h"

/* Utils */
void	cub_clear(t_cub *cub);
int		close_window(t_cub *cub);

/* Events */
void	register_hooks(t_cub *cub);

#endif