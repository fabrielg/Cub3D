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

typedef struct s_cub
{
	t_libx	libx;
}	t_cub;

#endif
