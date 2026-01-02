#include "map.h"
#include "parser.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_map_data	map;
	int			fd;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (get_map(fd, &map))
		return (1);
	debug_map(&map);
	check_textures(&map);
	return (0);
}
