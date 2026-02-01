#include "libft.h"
#include "cub3d.h"
#include "parser.h"

/**
 * @brief Parse the header lines of the map file and update map data.
 * @return 0 on success, 1 on error
 */
static int	map_parser(int fd, t_map *map)
{
	char			*line;
	char			*raw_grid;
	unsigned char	flags;
	size_t			line_size;

	flags = 0;
	line = get_next_line(fd);
	raw_grid = ft_calloc(1, sizeof(char));
	if (!raw_grid)
		return (1);
	while (line)
	{
		line_size = ft_strlen(line);
		if (line_size && line[line_size - 1] == '\n')
			line[line_size - 1] = 0;
		if (flags == (unsigned char)0b00111111)
		{
			raw_grid_parser(line, &raw_grid);
		}
		else if (line[0])
		{
			flags = header_parser(map, line, flags);
			if (!flags)
				return (free(line), 1);
		}
		free(line);
		line = get_next_line(fd);
	}
	create_grid(map, raw_grid);
	return (0);
}

/**
 * @brief Main function to parse the map file and fill the map data.
 * @return 0 on success, -1 on error
 */
int	get_map(int fd, t_map *map)
{
	if (fd < 0)
		return (-1);
	if (map_parser(fd, map) == 1)
		return (close(fd), 1);
	close(fd);
	if (check_grid(map->grid, map->widths) == 1)
		return (1);
	return (1); //DEBUG
	return (0);
}
