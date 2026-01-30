#ifndef PARSER_H
# define PARSER_H

# include "map.h"

// ============== MAP PARSING ============== //

int		get_map(int fd, t_map *map_data);
int		header_parser(t_map *data, char *line, unsigned char flag);
int		raw_grid_parser(char *line, char **raw_grid);
int		create_grid(t_map *map, char *raw_grid);

// ============== PARSING UTILS ============== //

char			*ft_strskip(char *line, char *charset);
unsigned int	rgb_from_split(char **split);
unsigned char	get_prefix(char *line);

// ============== MAP CHECKER ============== //

int		check_textures(t_map *map);

// ============== DEBUG ============== //

int		debug_map(t_map *map);

#endif
