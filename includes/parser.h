#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

# define B_NORTH	0b00000001
# define B_SOUTH	0b00000010
# define B_EAST		0b00000100
# define B_WEST		0b00001000
# define B_CELLING	0b00010000
# define B_FLOOR	0b00100000

// ============== MAP_PARSING ============== //

int			get_map(int fd, t_map *map_data);
int			header_parser(t_map *data, char *line, unsigned char flag);
int			raw_grid_parser(char *line, char **raw_grid);
int			create_grid(t_map *map, char *raw_grid);

// ============== PARSING_UTILS ============== //

char		*ft_strskip(char *line, char *charset);
int			is_str_digit(char *str);
_int32_t	rgb_from_split(char **split);
uint32_t	get_prefix(char *line);
int			check_extension(char *str, char *ext);

// ============== TEXTURES_UTILS ============== //

int			check_textures(t_map *map);
int			load_textures(t_libx *libx, t_map *map);

// ============== MAP_CHECKER ============== //

int			check_grid(char **grid, int *widths);

// ============== DEBUG ============== //

int			debug_map(t_map *map);

// ============== OTHER ============== //

void		free_map(t_map *map);

#endif
