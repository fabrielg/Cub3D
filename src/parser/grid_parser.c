#include "libft.h"
#include "map.h"
#include <math.h>

int	formated_line_len(char *line, char *f_line, const char *valid_charset)
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
			return (-1);//ERROR ILLEGAL CHAR USED
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

	f_len = formated_line_len(line, f_line, " 10NSOE");
	if (f_len == -1)
		return (NULL);//ERROR ILLEGAL CHAR USED
	f_line = get_formated_line(line, f_len);
	return (f_line);
}

int	raw_grid_parser(char *line, char **raw_grid)
{
	char	*f_line;
	char	*buff;

	buff = *raw_grid;
	if (!line || !line[0])
		return (0);
	if (!*raw_grid)
	{
		*raw_grid = ft_calloc(1, sizeof(char));
		if (!*raw_grid)
			return (1);
	}
	f_line = format_line(line);
	*raw_grid = ft_strjoin(*raw_grid, f_line);
	if (!*raw_grid)
		return (1);
	free(f_line);
	return (1);
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
