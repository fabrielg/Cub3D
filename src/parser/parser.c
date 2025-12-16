#include "libft.h"
#include "map.h"

#define NORTH "NO"
#define SOUTH "SO"
#define WEAST "WE"
#define EAST "EA"
#define CELLING "C"
#define FLOOR "F"

static t_list	*get_lines_from_file(int fd)
{
	t_list	*lines;
	char	*temp;

	lines = NULL;
	temp = get_next_line(fd);
	while (temp)
	{
		ft_lstadd_back(&lines, ft_lstnew(temp));
		temp = get_next_line(fd);
	}
	return (lines);
}

static int	values_parser(char **values)
{
	static const char	*args[6] = {NORTH, SOUTH, WEAST, EAST, CELLING, FLOOR};
	char				*value;
	int					i;

	if (!(*values))
		return (0);
	i = 0;
	while (values[i])
	{
		value = values[i];
		if (ft_strarr_has_str(args, value, 6))
		{
			// TODO: interpret TEXTURES and COLORS
		}
		printf("value: {%s}\n", value);
		i++;
	}
	return (0);
}

static int	data_parser(t_map_data *map_data, t_list *lines)
{
	t_list	*tmp;
	char	**split;

	(void)map_data;
	tmp = lines;
	while(tmp)
	{
		ft_printf("lines: %s", tmp->content);
		split = ft_split(tmp->content, ' ');
		if (!split)
			return (1);
		values_parser(split);
		ft_free_map((void**) split, -1);
		tmp = tmp->next;
	}
	return (0);
}

int	map_parser(int fd, t_map_data *map_data)
{
	t_list	*lines;

	if (fd < 0)
		return (-1);
	lines = get_lines_from_file(fd);
	close(fd);
	if (!lines)
		return (1);
	data_parser(map_data, lines);
	ft_lstclear(&lines, free);
	return (0);
}
