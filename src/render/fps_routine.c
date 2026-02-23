#include "cub3d.h"
#include "libft.h"
#include <sys/time.h>
#include <mlx_utils.h>

#define UPDATE_FPS_INTERVAL 500
#define UPDATE_DTIME_INTERVAL 1000

/**
 * @brief Get current time in microseconds.
 * @return Time in microseconds since epoch
 */
static long get_ticks(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * (long)1e6 + tv.tv_usec);
}

static float get_delta_time(long time)
{
	static long	last_time = 0;
	long		diff;
	float		delta;

	diff = time - last_time;
	if (last_time == 0)
		last_time = time;
	if (diff < UPDATE_DTIME_INTERVAL)
		diff = UPDATE_DTIME_INTERVAL;
	delta = (float)diff / (float)1e6;
	last_time = time;
	if (delta > 0.1f)
		delta = 0.1f;
	return (delta);
}

/**
 * @brief Update FPS counter based on elapsed time.
 * @return 1 if FPS updated, 0 otherwise
 */
static int	update_fps_counter(t_fps *fps, long time)
{
	static long	int last_fps_time = 0;

	if (last_fps_time == 0)
		last_fps_time = time;
	fps->frame_count++;
	if ((time - last_fps_time) / 1000L >= UPDATE_FPS_INTERVAL)
	{
		fps->fps = fps->frame_count * 1000 / UPDATE_FPS_INTERVAL;
		fps->frame_count = 0;
		last_fps_time = time;
		return (1);
	}
	return (0);
}

/**
 * @brief Render current FPS on the window.
 */
void	show_fps(t_cub *cub)
{
	char	*fps_s;

	draw_text(&cub->libx, "FPS :", WIN_WIDTH - 100, 15);
	fps_s = ft_itoa(cub->fps.fps);
	if (!fps_s)
		return ;
	draw_text(&cub->libx, fps_s, WIN_WIDTH - 50, 15);
	free (fps_s);
}

/**
 * @brief Main routine to update FPS and delta time per frame.
 * @return 0 on success
 */
int	fps_routine(t_cub *cub)
{
	long	time;

	time = get_ticks();
	cub->fps.delta_time = get_delta_time(time);
	if (!update_fps_counter(&cub->fps, time))
		return (0);
	mlx_put_image_to_window(cub->libx.mlx, cub->libx.window,
		cub->libx.game_img.img, 0, 0);
	mlx_put_image_to_window(cub->libx.mlx, cub->libx.window, 
		cub->libx.minimap_img.img, WIN_WIDTH - MINIMAP_SIZE - 10, 10);
	show_fps(cub);
	return (0);
}
