#include "libft.h"
#include "cub3d.h"

#define VALID_CHARSET " 10NSWE"
#define ERR_INVALID_CHAR "Error: Invalid char used in grid '%c'\n"
#define ERR_EMPTY_GRID_LINE "Error: Empty line in grid\n"

int	formated_line_len(char *line, const char *valid_charset)
{
	int	i;
	int	extra_space;

	i = -1;
	extra_space = 0;
	while (line[++i])
	{
		if (line[i] == 9)
			extra_space += 3;
		else if (!ft_strchr(valid_charset, line[i]))
			return (printf(ERR_INVALID_CHAR, line[i]), -1);
	}
	return (i + extra_space);
}

char	*get_formated_line(char *line, int f_len)
{
	char	*f_line;
	int		i;
	int		j;
	int		space;

	i = -1;
	j = -1;
	f_line = ft_calloc(f_len + 2, sizeof(char));
	if (!f_line)
		return (NULL);
	while (++i < f_len)
	{
		if (line[++j] == 9)
		{
			space = 0;
			while (space++ < 4 && i < f_len)
				f_line[i++] = ' ';
			i--;
		}
		else
			f_line[i] = line[j];
	}
	f_line[i] = ',';
	return (f_line);
}

char	*format_line(char *line)
{
	char	*f_line;
	int		f_len;

	f_len = formated_line_len(line, VALID_CHARSET);
	if (f_len == -1)
		return (NULL);
	f_line = get_formated_line(line, f_len);
	return (f_line);
}

int	raw_grid_parser(char *line, char **raw_grid)
{
	char	*f_line;
	char	*tmp;

	tmp = *raw_grid;
	if (!line || !line[0])
		return (!!*raw_grid[0] && printf(ERR_EMPTY_GRID_LINE));
	f_line = format_line(line);
	if (!f_line)
		return (1);
	*raw_grid = ft_strjoin(tmp, f_line);
	if (!*raw_grid)
		return (free(f_line), free(tmp), 1);
	return (free(f_line), free(tmp), 0);
}

int	create_grid(t_map *map, char *raw_grid)
{
	int	i;

	i = -1;
	map->grid = ft_split(raw_grid, ',');
	map->max_height = ft_strarrlen(map->grid);
	map->widths = ft_calloc(map->max_height, sizeof(int));
	if (!map->widths)
		return (1);
	while(++i  < map->max_height)
		map->widths[i] = ft_strlen(map->grid[i]);
	return (0);
}
