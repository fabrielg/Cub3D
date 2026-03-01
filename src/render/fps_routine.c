#include "cub3d.h"
#include "libft.h"
#include <sys/time.h>
#include <mlx_utils.h>

/**
 * @brief Get current time in microseconds.
 * @return Time in microseconds since epoch
 */
static long	get_ticks(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * (long)1e6 + tv.tv_usec);
}

/**
 * @brief get delta time in seconds between frames.
 * @return Delta time in seconds with safety limits
 */
static float get_delta_time(long time, int update_dtime_interval)
{
	static long	last_time = 0;
	long		diff;

	if (last_time == 0)
	{
		last_time = time;
		return (0.0f);
	}
	diff = time - last_time;
	last_time = time;
	if (diff < update_dtime_interval)
		diff = update_dtime_interval;

	if (diff > 10000L)
		diff = 10000L;
	return ((float)diff / 1e6f);
}

/**
 * @brief Update FPS counter based on elapsed time.
 * @return 1 if FPS updated, 0 otherwise
 */
static int	update_fps_counter(t_fps *fps, long time, int update_fps_interval)
{
	static long	last_fps_time = 0;

	if (last_fps_time == 0)
		last_fps_time = time;
	fps->frame_count++;
	if ((time - last_fps_time) / 1000L >= update_fps_interval)
	{
		fps->fps = fps->frame_count * 1000 / update_fps_interval;
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

	draw_text(&cub->libx, "FPS :", cub->config.fps_x - 50, cub->config.fps_y);
	fps_s = ft_itoa(cub->fps.fps);
	if (!fps_s)
		return ;
	draw_text(&cub->libx, fps_s, cub->config.fps_x, cub->config.fps_y);
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
	cub->fps.delta_time = get_delta_time(time, cub->config.update_dtime_interval);
	if (update_fps_counter(&cub->fps, time, cub->config.update_fps_interval))
		show_fps(cub);
	return (0);
}
