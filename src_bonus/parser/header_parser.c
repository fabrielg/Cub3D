/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:33:58 by alde-abr          #+#    #+#             */
/*   Updated: 2026/03/02 20:33:59 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "cub3d.h"
#include <math.h>

#define ERR_HEADER_REP "Error: Multiple definition in header\n"
#define ERR_TXTR_EXTENSION "Error: Texture \"%s\" need [.xpm] extension\n"
#define ERR_TXTR_INVALID "Error: Invalid texture\n"

/**
 * @brief Check header flag duplication and update flags.
 * @return Current flag value or 0 on repetition error
 */
static int	check_flag_repetition(char *line, t_uint32 *flags)
{
	t_uint32	current_flag;

	current_flag = get_prefix(line);
	if (current_flag & *flags)
		return (printf(ERR_HEADER_REP), 0);
	*flags |= current_flag;
	return (current_flag);
}

/**
 * @brief Parse a texture (NO, SO, EA, WE) and store its path in map data.
 * @return 0 on success, 1 on error
 */
static int	texture_parser(t_map *map, char *line, t_uint32 flag)
{
	char	*texture;
	int		texture_id;

	texture = ft_strskip(line, " \f\r\t");
	if (!texture || !texture[0])
		return (printf(ERR_TXTR_INVALID), 1);
	texture = ft_strskip(texture + 2, " \f\r\t");
	if (check_extension(texture, ".xpm"))
		return (printf(ERR_TXTR_EXTENSION, texture), 1);
	texture_id = log2(flag);
	map->raw_textures[texture_id] = ft_strdup(texture);
	if (!map->raw_textures[texture_id])
		return (1);
	return (0);
}

/**
 * @brief Parse a color line and store it in the map data structure.
 * @return 0 on success, 1 on error
 */
t_int32	color_parser(t_map *map, char *line, t_uint32 flag)
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
	if (rgb_from_split(split, &map->colors[color_id]) == 1)
		return (ft_free_map((void **)split, -1), 1);
	ft_free_map((void **)split, -1);
	return (0);
}

/**
 * @brief Call the correct parser depending on the line flag type.
 */
int	header_parser(t_map *map, char *line, t_uint32 flag)
{
	t_uint32	current_flag;

	current_flag = check_flag_repetition(line, &flag);
	if (!current_flag)
		return (0);
	if (current_flag & 0b00001111)
	{
		if (texture_parser(map, line, current_flag))
			return (0);
	}
	else if (current_flag & 0b00110000)
	{
		if (color_parser(map, line, current_flag))
			return (0);
	}
	return (flag);
}
