#include "libft.h"
#include "cub3d.h"
#include "parser.h"

/**
 * @brief Free parser resources, clear GNL buffer and close fd.
 * @return 1
 */
static int	free_map_parser(char *line, char *r_grid)
{
	if (r_grid)
	{
		free(r_grid);
		r_grid = NULL;
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
	get_next_line(-42);
	return (1);
}

/**
 * @brief Remove trailing newline character from string.
 */
static void	nullset_last_char(char *str)
{
	size_t	str_size;

	str_size = ft_strlen(str);
	if (str_size && str[str_size - 1] == '\n')
		str[str_size - 1] = '\0';
}

/**
 * @brief Process line as header or grid based on flags.
 * @return 0 on success, 1 on parsing error
 */
static int	get_content(t_map *map, char *line, uint32_t *flags, char **r_grid)
{
	if (*flags == (uint32_t)0b00111111)
	{
		if (raw_grid_parser(line, r_grid) == 1)
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
	char		*line;
	char		*raw_grid;
	uint32_t	flags;

	flags = 0;
	line = get_next_line(fd);
	raw_grid = ft_calloc(1, sizeof(char));
	if (!raw_grid)
		return (1);
	while (line)
	{
		nullset_last_char(line);
		if (get_content(map, line, &flags, &raw_grid) == 1)
			return (free_map_parser(line, raw_grid));
		free(line);
		line = get_next_line(fd);
	}
	if (create_grid(map, raw_grid) == 1)
		return (free(raw_grid), 1);
	return (free(raw_grid), 0);
}

/**
 * @brief Main function to parse the map file and fill the map data.
 * @return 0 on success, 1 on error
 */
int	get_map(int fd, t_map *map)
{
	if (map_parser(fd, map) == 1)
		return (1);
	if (check_grid(map->grid, map->widths) == 1)
		return (1);
	return (0);
}
