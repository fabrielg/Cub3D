#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "cub3d.h"
# include <mlx.h>

/* Utils */

void	mlx_clear(t_libx *libx);
int		close_window(t_cub *cub);
void	draw_text(t_libx *libx, char *str, int x, int y);

/* Events */

void	register_hooks(t_cub *cub);

/* Draw */

void	draw_square(t_img_data *img, int x, int y, int size, int color);

#endif
