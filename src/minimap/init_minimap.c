#include "cub3d.h"
#include "libft.h"
#include "mlx_utils.h"

#define MINIMAP_CELL MINIMAP_SIZE / 5
#define VOID_COLOR	0x666666
#define WALL_COLOR	0x777777
#define FLOOR_COLOR	0xFFFFFF

//MINIMAP SIZE FUNC //TODO

void	init_minimap(t_libx *libx)
{
	libx->minimap_img.img = mlx_new_image(
			libx->mlx,
			MINIMAP_SIZE,
			MINIMAP_SIZE);
	libx->minimap_img.addr = mlx_get_data_addr(
			libx->minimap_img.img,
			&libx->minimap_img.bits_per_pixel,
			&libx->minimap_img.line_length,
			&libx->minimap_img.endian);
}

static int	get_cell_color(int x, int y, t_map *map)
{
	if (x < 0 || y < 0 || y >= map->max_height || x >= map->widths[y])
		return (VOID_COLOR);
	if (map->grid[y][x] == '1' || map->grid[y][x] == ' ')
		return (WALL_COLOR);
	return (FLOOR_COLOR);
}

void	render_minimap(t_libx *libx, t_player *p, t_map *map)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			color = get_cell_color(
					(x - 2) + (int)p->position[0],
					(y - 2) + (int)p->position[1],
					map);
			draw_square(&libx->minimap_img, x * MINIMAP_CELL, y * MINIMAP_CELL, 
				MINIMAP_CELL, color);
			x++;
		}
		y++;
	}
}
