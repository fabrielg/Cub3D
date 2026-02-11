#include "libft.h"
#include "cub3d.h"
#include "parser.h"

#define HEADER_ERROR "Error: parsing error (invalid header)\n"

static int	free_map_parser(char *line, char *raw_grid, int fd)
{
	if (raw_grid)
	{
		free(raw_grid);
		raw_grid = NULL;
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
	get_next_line(-42);
	close(fd);
	return (1);
}

static void	nullset_last_char(char *str)
{
	size_t	str_size;

	str_size = ft_strlen(str);
	if (str_size && str[str_size - 1] == '\n')
		str[str_size - 1] = '\0';
}

static int	get_map_content(t_map *map, char *line, unsigned char *flags, char **raw_grid)
{
	if (*flags == (unsigned char)0b00111111)
	{
		if (raw_grid_parser(line, raw_grid) == 1)
			return (1);
	}
	else if (line[0])
	{
		*flags = header_parser(map, line, *flags);
		if (!*flags)
			return (1);
	}
	return (0);
}

/**
 * @brief Parse the header lines of the map file and update map data.
 * @return 0 on success, 1 on error
 */
static int	map_parser(int fd, t_map *map)
{
	char			*line;
	char			*raw_grid;
	unsigned char	flags;

	flags = 0;
	line = get_next_line(fd);
	raw_grid = ft_calloc(1, sizeof(char));
	if (!raw_grid)
		return (1);
	while (line)
	{
		nullset_last_char(line);
		if (get_map_content(map, line, &flags, &raw_grid) == 1)
			return (free_map_parser(line, raw_grid, fd));
		free(line);
		line = get_next_line(fd);
	}
	if (create_grid(map, raw_grid) == 1)
		return (free(raw_grid), 1);
	return (free(raw_grid), 0);
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
		return (1);
	if (check_grid(map->grid, map->widths) == 1)
		return (1);
	printf("success\n");
	return (0);
}
