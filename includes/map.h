#ifndef MAP_H
# define MAP_H

typedef struct s_map_data
{
	char			textures[4];
	unsigned int	celling_color;
	unsigned int	floor_color;
	char			**grid;
	int				*widths;
	int				max_height;
}	t_map_data;

#endif