#include "cub3d.h"
#include "libft.h"

/**
 * @brief Toggle the door state in front of the player.
 * @return 0 if success, 1 if target is current tile
 */
int	interact_with_door(t_cub *cub)
{
	int	target_x;
	int	target_y;

	target_x = (int)(cub->player.position[0]
		+ cosf(cub->player.angle_view) * 1.2f);
	target_y = (int)(cub->player.position[1]
		+ sinf(cub->player.angle_view) * 1.2f);
	if ((int)(cub->player.position[0]) == target_x
		&& (int)(cub->player.position[1]) == target_y)
		return (1);
	if (cub->map.grid[target_y][target_x] == 'C')
		cub->map.grid[target_y][target_x] = 'O';
	else if (cub->map.grid[target_y][target_x] == 'O')
		cub->map.grid[target_y][target_x] = 'C';
	return (0);
}

/**
 * @brief Update door animation frame based on elapsed delta time.
 */
void	update_door(t_door *door, t_fps *fps)
{
	door->timer += fps->delta_time;

	if (door->timer >= door->frame_duration)
	{
		door->timer = 0.0f;
		door->current_frame++;
		door->current_frame %= 3;
	}
}
