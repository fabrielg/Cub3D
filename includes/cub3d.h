#ifndef CUB3D_H
# define CUB3D_H

# define WIN_WIDTH 1600
# define WIN_HEIGHT 900
# define WIN_TITLE "Cub3D"

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

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
}   t_direction;

typedef struct s_map
{
	char			*textures[4];
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

void	init_player(t_map *map, t_player *player);
void	draw_vertical_line(t_img_data *img, int x, int y_start, int y_end, int color);

#endif
