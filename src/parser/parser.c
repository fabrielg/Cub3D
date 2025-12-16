#include "libft.h"
#include "map.h"

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

int	map_parser(int fd, t_map_data *map_data)
{
	t_list	*lines;

	(void)map_data;
	if (fd < 0)
		return (-1);
	lines = get_lines_from_file(fd);
	close(fd);
	if (!lines)
		return (1);
	ft_lstclear(&lines, free);
	return (0);
}
