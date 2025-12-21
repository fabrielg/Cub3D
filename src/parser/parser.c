#include "libft.h"
#include "map.h"
#include <math.h>

static char	*ft_strskip(char *line, char *charset)
{
	int		i;

	if (!charset)
		return (line);
	i = -1;
	while (line[++i])
	{
		if (!ft_strchr(charset, line[i]))
			break ;
	}
	return (line + i);
}

static int	texture_parser(t_map_data *data, char *line, unsigned char flag)
{
	char	*texture;
	int		texture_id;

	printf("BEFORE: [%s]\n", line);
	texture = ft_strskip(line, " \f\r\t");
	if (!texture || !texture[0])
		return (1);
	texture = ft_strskip(texture + 2, " \f\r\t");
	printf("AFTER: [%s]\n", texture);
	texture_id = log2(flag);
	data->textures[texture_id] = ft_strdup(texture);
	return (0);
}

static unsigned int	rgb_from_split(char **split)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);

	return ((r << 16) | (g << 8) | b);
}

static int	color_parser(t_map_data *data, char *line, unsigned char flag)
{
	char	*color_str;
	char	**split;
	int		color_id;

	color_str = ft_strskip(line + 2, " \f\r\t");
	if (!color_str || !color_str[0])
		return (1);
	split = ft_split(color_str, ',');
	if (!split || ft_strarrlen(split) != 3)
		return (ft_free_map((void **)split, -1), 1);
	color_id = log2(flag) - 4;
	data->colors[color_id] = rgb_from_split(split);
	ft_free_map((void **)split, -1);
	return (0);
}

static void	header_parser(t_map_data *data, char *line, unsigned char flag)
{
	if (flag & 0b00001111)
		texture_parser(data, line, flag);
	else if (flag & 0b00110000)
		color_parser(data, line, flag);
}

static unsigned char	get_prefix(char *line)
{
	static const char	*args[6] = {"NO", "SO", "EA", "WE", "C", "F"};
	char	*tmp;
	int		size;
	int		i;

	tmp = ft_strskip(line, " \f\r\t");
	if (!tmp || !tmp[0])
		return (0);
	size = 0;
	while (tmp[size] != ' ' && tmp[size])
		size++;
	i = -1;
	while (args[++i])
	{
		if (ft_strncmp(tmp, args[i], size) == 0)
			break ;
	}
	if (i >= 6)
		return (0);
	return (1 << i);
}

static int	map_parser(int fd, t_map_data *map_data)
{
	char			*line;
	unsigned char	current_flag;
	unsigned char	flags;
	size_t			line_size;

	flags = 0;
	line = get_next_line(fd);
	while (line)
	{
		line_size = ft_strlen(line);
		if (line_size && line[line_size - 1] == '\n')
			line[line_size - 1] = 0;
		if (flags & 0b00111111)
		{
			// Check the grid
		}
		else if (line[0])
		{
			current_flag = get_prefix(line);
			printf("current_flag: %d\n", current_flag);
			printf("flags: %d\n", flags);
			if (current_flag & flags)
				return (1); // ERROR: can't have 2 times the same data
			flags &= current_flag;
			header_parser(map_data, line, current_flag);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	get_map(int fd, t_map_data *map_data)
{
	if (fd < 0)
		return (-1);
	map_parser(fd, map_data);
	close(fd);
	// DEBUG
	printf("--- DEBUG ---\n");
	for (int i = 0; i < 4; i++)
	{
		printf("%i %s\n", i, map_data->textures[i]);
		free(map_data->textures[i]);
	}
	for (int i = 0; i < 2; i++)
	{
		printf("%i %i\n", i, map_data->colors[i]);
	}
	return (0);
}
