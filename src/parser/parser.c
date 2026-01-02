#include "libft.h"
#include "map.h"
#include "parser.h"
#include <math.h>

/**
 * @brief Parse the header lines of the map file and update map data.
 * @return 0 on success, 1 on error
 */
static int	map_parser(int fd, t_map_data *map_data)
{
	char			*line;
	unsigned char	flags;
	size_t			line_size;

	flags = 0;
	line = get_next_line(fd);
	while (line)
	{
		line_size = ft_strlen(line);
		if (line_size && line[line_size - 1] == '\n')
			line[line_size - 1] = 0;
		if (flags == (unsigned char)0b00111111)
		{
			//TODO
		}
		else if (line[0])
		{
			flags = header_parser(map_data, line, flags);
			ft_putbits(flags);
			if (!flags)
				return (free(line), 1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

/**
 * @brief Main function to parse the map file and fill the map data.
 * @return 0 on success, -1 on error
 */
int	get_map(int fd, t_map_data *map_data)
{
	if (fd < 0)
		return (-1);
	map_parser(fd, map_data);
	close(fd);
	return (0);
}
