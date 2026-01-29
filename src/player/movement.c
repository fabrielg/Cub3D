#include "cub3d.h"
#include <math.h>

#define MOVE_SPEED 0.1f
#define ROT_SPEED 0.05f

int	move_forward(t_cub *cub)
{
	float	new_x;
	float	new_y;

	new_x = cub->player.position[0] + cosf(cub->player.angle_view) * MOVE_SPEED;
	new_y = cub->player.position[1] + sinf(cub->player.angle_view) * MOVE_SPEED;
	
	if (cub->map.grid[(int)new_y][(int)new_x] != '1')
	{
		cub->player.position[0] = new_x;
		cub->player.position[1] = new_y;
	}
	return (0);
}

int	move_backward(t_cub *cub)
{
	float	new_x;
	float	new_y;

	new_x = cub->player.position[0] - cosf(cub->player.angle_view) * MOVE_SPEED;
	new_y = cub->player.position[1] - sinf(cub->player.angle_view) * MOVE_SPEED;
	
	if (cub->map.grid[(int)new_y][(int)new_x] != '1')
	{
		cub->player.position[0] = new_x;
		cub->player.position[1] = new_y;
	}
	return (0);
}

int	rotate_left(t_cub *cub)
{
	cub->player.angle_view -= ROT_SPEED;
	return (0);
}

int	rotate_right(t_cub *cub)
{
	cub->player.angle_view += ROT_SPEED;
	return (0);
}