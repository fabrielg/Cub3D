#ifndef PARSER_H
# define PARSER_H

# include "map.h"

int	get_map(int fd, t_map_data *map_data);
int	check_textures(t_map_data *map);
int	debug_map(t_map_data *map);
void	fill_map(t_map_data *map);

#endif
