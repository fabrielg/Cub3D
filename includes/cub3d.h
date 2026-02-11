#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>

# define WIN_WIDTH		1600
# define WIN_HEIGHT		900
# define WIN_TITLE		"Cub3D"

# define FOV			M_PI / 3
# define TILE_SIZE		1.0
# define DIST_PROJ		(WIN_WIDTH / 2) / tan(FOV / 2)

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

typedef struct s_texture
{
	t_img_data	img_data;
	int			size;
}	t_texture;

typedef struct s_libx
{
	void		*mlx;
	void		*window;
	t_img_data	img_data;
}	t_libx;

typedef enum e_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_direction;

typedef struct s_map
{
	char			*raw_textures[4];
	t_texture		textures[4];
	unsigned int	colors[2];
	char			**grid;
	int				*widths;
	int				max_height;
	int				default_position[2];
	t_direction		default_direction;
}	t_map;

typedef struct s_player
{
	float	position[2];
	float	angle_view;
}	t_player;

typedef struct s_cub
{
	t_libx		libx;
	t_map		map;
	t_player	player;
}	t_cub;

typedef struct s_ray_data
{
	float		dir_x;
	float		dir_y;
	int			map_x;
	int			map_y;
	float		delta_dist_x;
	float		delta_dist_y;
	float		side_dist_x;
	float		side_dist_y;
	int			step_x;
	int			step_y;
	int			side;
	t_direction	hit_side;
	float		distance;
}	t_ray_data;

typedef struct s_column
{
	float		angle;
	int			wall_height;
	int			y_start;
	int			y_end;
	int			texture_x;
	t_ray_data	raycast;
}	t_column;

/* Drawing */
void		put_pixel(t_img_data *data, int x, int y, int color);
int			get_texture_pixel(t_texture *texture, int tex_x, int tex_y);

/* Rendering */
float		get_ray_angle(t_player *p, int x);
void		init_ray_direction(t_ray_data *ray, float angle, float pos[2]);
t_ray_data	get_wall_distance(t_map *map, t_player *p, float angle);
void		get_wall_slice(t_column *col, float distance);
int			get_texture_x(t_ray_data *raycast, float pos[2], t_texture textures[4]);
void		draw_vertical_line(t_img_data *img, int x, int y_start, int y_end, int color);
void		render_frame(t_libx *libx, t_map *map, t_player *p);
t_ray_data	dda(char **grid, float p_position[2], float ray_angle);

/* Player */
void		init_player(t_map *map, t_player *player);
float		get_cardinal_angle(t_direction direction);
int			move_forward(t_cub *cub);
int			move_backward(t_cub *cub);
int			move_left(t_cub *cub);
int			move_right(t_cub *cub);
int			rotate_left(t_cub *cub);
int			rotate_right(t_cub *cub);
int			respawn(t_cub *cub);

#endif
