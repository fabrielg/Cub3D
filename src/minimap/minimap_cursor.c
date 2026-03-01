#include "cub3d.h"
#include "mlx_utils.h"
#include "minimap.h"

/**
 * @brief Convert player angle to cardinal direction index.
 * @return Direction index from 0 to 3
 */
static int	get_player_dir(float angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle >= 7 * M_PI / 4 || angle < M_PI / 4)
		return (3);
	else if (angle >= M_PI / 4 && angle < 3 * M_PI / 4)
		return (0);
	else if (angle >= 3 * M_PI / 4 && angle < 5 * M_PI / 4)
		return (2);
	return (1);
}

/**
 * @brief Draw player cursor on minimap by direction.
 * @note Direction : [0]up, [1]down, [2]left, [3]right
 */
static void	draw_cursor(t_libx *libx, int x, int y, int direction)
{
	int	i;
	int	size;

	size = libx->minimap_size / 9;
	i = -1;
	if (direction == 0)
		while (++i < size)
			draw_horizontal_line(&libx->minimap_img,
				(int [2]){x - (size / 2 - i), x + (size / 2 - i)},
				y + (i - size / 4), CURSOR_COLOR);
	else if (direction == 1)
		while (++i < size)
			draw_horizontal_line(&libx->minimap_img,
				(int [2]){x - (size / 2 - i), x + (size / 2 - i)},
				y - (i - size / 4), CURSOR_COLOR);
	else if (direction == 2)
		while (++i <= size / 2)
			draw_vertical_line(&libx->minimap_img, x + (i - size / 4),
				(int [2]){y - i, y + i}, CURSOR_COLOR);
	else if (direction == 3)
		while (++i <= size / 2)
			draw_vertical_line(&libx->minimap_img, x - (i - size / 4),
				(int [2]){y - i, y + i}, CURSOR_COLOR);
}

/**
 * @brief Render player cursor at minimap center.
 */
void	render_cursor(t_libx *libx, t_player *p)
{
	int	dir;

	dir = get_player_dir(p->angle_view);
	draw_cursor(libx, libx->minimap_size / 2, libx->minimap_size / 2, dir);
}
