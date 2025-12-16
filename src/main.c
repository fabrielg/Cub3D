#include "map.h"
#include "parser.h"
#include <unistd.h>
#include <fcntl.h>

int	main(int argc, char *argv[])
{
	t_map_data	data;
	int			fd;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (map_parser(fd, &data))
		return (1);
	return (0);
}