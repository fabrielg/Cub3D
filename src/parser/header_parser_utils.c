/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_parser_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 20:32:21 by alde-abr          #+#    #+#             */
/*   Updated: 2026/03/02 20:32:22 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

#define ERR_INVALID_HEADER_CHAR "Error: Invalid line in header \"%s\"\n"
#define ERR_INVALID_COLOR "Error: Invalid color values \"%s,%s,%s\"\n"

/**
 * @brief Skip leading characters from charset and return new line pointer.
 * @return Pointer to first character not in charset
 */
char	*ft_strskip(char *line, char *charset)
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

/**
 * @brief Get the digits from a RGB string.
 * @return 0 if valid, 1 otherwise.
 */
int	ft_atoi_rgb(char *str, int *out)
{
	int	i;
	int	result;

	i = -1;
	result = 0;
	while (str[++i])
	{
		if (ft_strchr(" \t\r\f", str[i]))
			continue ;
		if (result > 255 || !ft_isdigit(str[i]))
			return (1);
		result = result * 10 + (str[i] - '0');
	}
	if (result > 255)
		return (1);
	*out = result;
	return (0);
}

/**
 * @brief Convert an RGB array of strings to a packed 24-bit color,
 * out the RGB int color.
 * @return Integer representing the RGB color
 */
int	rgb_from_split(char **split, t_int32 *out)
{
	int	r;
	int	g;
	int	b;

	if (ft_atoi_rgb(split[0], &r) || ft_atoi_rgb(split[1], &g)
		|| ft_atoi_rgb(split[2], &b))
		return (printf(ERR_INVALID_COLOR, split[0], split[1], split[2]), 1);
	*out = (t_int32)((r << 16) | (g << 8) | b);
	return (0);
}

/**
 * @brief Identify the prefix of a line and return its corresponding flag.
 * @return Bit flag corresponding to the line prefix
 */
t_uint32	get_prefix(char *line)
{
	static const char	*args[7] = {"NO", "SO", "EA", "WE", "C", "F"};
	char				*tmp;
	int					size;
	int					i;

	tmp = ft_strskip(line, " \f\r\t");
	if (!tmp || !tmp[0])
		return (0);
	size = 0;
	while (tmp[size] != ' ' && tmp[size])
		size++;
	i = -1;
	while (args[++i])
	{
		if (ft_strncmp(tmp, args[i], ft_max(size, ft_strlen(args[i]))) == 0)
			break ;
	}
	if (i >= 6)
		return (printf(ERR_INVALID_HEADER_CHAR, tmp), 0);
	return (1 << i);
}
