#ifndef PARSER_H
# define PARSER_H

# include "map.h"

// ============== MAP PARSING ============== //

int		get_map(int fd, t_map_data *map_data);
int		header_parser(t_map_data *data, char *line, unsigned char flag);

// ============== PARSING UTILS ============== //

char			*ft_strskip(char *line, char *charset);
unsigned int	rgb_from_split(char **split);
unsigned char	get_prefix(char *line);

// ============== MAP CHECKER ============== //

int		check_textures(t_map_data *map);


// ============== DEBUG ============== //

int		debug_map(t_map_data *map);

#endif
