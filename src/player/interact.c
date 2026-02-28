#include "cub3d.h"
#include "libft.h"

int	open_door(t_cub *cub)
{
	int	target_x;
	int	target_y;

	target_x = (int)(cub->player.position[0]
		+ cosf(cub->player.angle_view) * 1.0f);
	target_y = (int)(cub->player.position[1]
		+ sinf(cub->player.angle_view) * 1.0f);
	if (cub->map.grid[target_y][target_x] == 'C')
		cub->map.grid[target_y][target_x] = 'O';
	return (0);
}

void	update_door(t_door *door, t_fps *fps)
{
	door->timer += fps->delta_time;

	if (door->timer >= door->frame_duration)
	{
		door->timer = 0.0f;
		door->current_frame++;
		door->current_frame %= 3; // boucle 0 1 2
	}
}
