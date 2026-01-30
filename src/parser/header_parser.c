#include "libft.h"
#include "parser.h"
#include <math.h>

static int	check_flag_repetition(char *line, unsigned char *flags)
{
	unsigned char	current_flag;

	current_flag = get_prefix(line);
	if (current_flag & *flags)
		return (printf("error\n"), 0); //ERROR TODO
	*flags |= current_flag;
	return (current_flag);
}

/**
 * @brief Parse a texture (NO, SO, EA, WE) and store its path in map data.
 * @return 0 on success, 1 on error
 */
static int	texture_parser(t_map *data, char *line, unsigned char flag)
{
	char	*texture;
	int		texture_id;

	texture = ft_strskip(line, " \f\r\t");
	if (!texture || !texture[0])
		return (1);
	texture = ft_strskip(texture + 2, " \f\r\t");
	texture_id = log2(flag);
	data->textures[texture_id] = ft_strdup(texture);
	return (0);
}

/**
 * @brief Parse a color line and store it in the map data structure.
 * @return 0 on success, 1 on error
 */
static int	color_parser(t_map *data, char *line, unsigned char flag)
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

/**
 * @brief Call the correct parser depending on the line flag type.
 */
int	header_parser(t_map *data, char *line, unsigned char flag)
{
	unsigned char	current_flag;

	current_flag = check_flag_repetition(line, &flag);
	if (!current_flag)
		return (0);
	if (current_flag & 0b00001111)
		texture_parser(data, line, current_flag);
	else if (current_flag & 0b00110000)
		color_parser(data, line, current_flag);
	return (flag);
}
