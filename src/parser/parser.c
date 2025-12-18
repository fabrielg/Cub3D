#include "libft.h"
#include "map.h"

int	get_map(int fd, t_map_data *map_data)
{
	if (fd < 0)
		return (-1);
	//loop line
	close(fd);
	return (0);
}

//loopline
//get line *line
//flag
//verif 3 cases (color, texture, grid)
static int	map_parser(int fd, t_map_data *map_data)
{
	char			*line;
	unsigned char	flag;

	flag = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		if (flag & 0b00111111)
		{
			// Check the grid
		}
		else
		{
			// Still check header
		}
		line = get_next_line(fd);
	}
}

static unsigned char	get_prefix(char *line)
{
	static const char	*args[6] = {"NO", "SO", "EA", "WE", "C", "F"};
	char	*tmp;
	int		size;
	int		i;

	if (!line[0])
		return (0);
	tmp = ft_strskip(line, " \f\r\t");
	size = 0;
	while (tmp[size] != " " && tmp[size])
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

//texture case
//verif if already ok

//color case

//grid case

//error case
