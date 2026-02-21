#include "cub3d.h"
#include "libft.h"
#include <sys/time.h>
#include <stdio.h>
#include <mlx_utils.h>

static long	get_ticks(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

// static void	draw_hard_rect(t_libx *libx)
// {
// 	int	x;

// 	x = 0;
// 	while (++x < 100)
// 	{
// 		draw_vertical_line(&libx->img_data, x, 10, WIN_HEIGHT - 1, 0xFFFFFF);
// 	}
// }

int	update_fps(t_cub *cub)
{
	char	*fps_s;

	cub->fps.time = get_ticks();
	if (cub->fps.old_time == 0)
		cub->fps.old_time = cub->fps.time;
	cub->fps.frame_count++;
	if (cub->fps.time - cub->fps.old_time >= 1000)
	{
		cub->fps.fps = cub->fps.frame_count;
		cub->fps.frame_count = 0;
		cub->fps.old_time = cub->fps.time;
	}
	else
		return (0);
	mlx_put_image_to_window(
		cub->libx.mlx,
		cub->libx.window,
		cub->libx.img_data.img,
		0, 0);
	draw_text(&cub->libx, "FPS :", WIN_WIDTH - 100, 15);
	fps_s = ft_itoa(cub->fps.fps);
	draw_text(&cub->libx, fps_s, WIN_WIDTH - 50, 15);
	return (free (fps_s), 0);
}

int	show_fps(t_cub *cub)
{
	char	*fps_s;

	cub->fps.time = get_ticks();
	if (cub->fps.old_time == 0)
		cub->fps.old_time = cub->fps.time;
	cub->fps.frame_count++;
	draw_text(&cub->libx, "FPS :", WIN_WIDTH - 100, 15);
	fps_s = ft_itoa(cub->fps.fps);
	draw_text(&cub->libx, fps_s, WIN_WIDTH - 50, 15);
	return (free (fps_s), 0);
}
