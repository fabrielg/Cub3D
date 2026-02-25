#include "cub3d.h"
#include "mlx_utils.h"
#include "minimap.h"

/**
 * @brief Get minimap cell color based on map position.
 * @return Color value for the specified cell
 */
static int	get_cell_color(int x, int y, t_map *map)
{
	if (x < 0 || y < 0 || y >= map->max_height || x >= map->widths[y])
		return (VOID_COLOR);
	if (map->grid[y][x] == '1' || map->grid[y][x] == ' ')
		return (WALL_COLOR);
	return (FLOOR_COLOR);
}

/**
 * @brief Render visible minimap cells around player.
 */
static void	render_minimap_cells(t_libx *libx, t_player *p, t_map *map)
{
	int	x;
	int	y;
	int	color;
	int	size;

	size = libx->minimap_size / 7;
	y = 0;
	while (y < 7)
	{
		x = 0;
		while (x < 7)
		{
			color = get_cell_color(
					(x - 3) + (int)p->position[0],
					(y - 3) + (int)p->position[1],
					map);
			draw_square(&libx->minimap_img, x * size, y * size, size, color);
			x++;
		}
		y++;
	}
}

/**
 * @brief Render full minimap including player cursor.
 */
void	render_minimap(t_libx *libx, t_player *p, t_map *map)
{
	render_minimap_cells(libx, p, map);
	render_cursor(libx, p);
}
