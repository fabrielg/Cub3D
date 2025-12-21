#ifndef MAP_H
# define MAP_H

# define B_NORTH	0b00000001
# define B_SOUTH	0b00000010
# define B_EAST		0b00000100
# define B_WEST		0b00001000
# define B_CELLING	0b00010000
# define B_FLOOR	0b00100000

typedef struct s_map_data
{
	char			*textures[4];
	unsigned int	colors[2];
	char			**grid;
	int				*widths;
	int				max_height;
}	t_map_data;

#endif