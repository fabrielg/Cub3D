#include "libft.h"
#include "cub3d.h"

#define ERR_INVALID_HEADER_CHAR "Error: Invalid line in header \"%s\"\n"
#define ERR_INVALID_COLOR "Error: Invalid color value \"%s\"\n"

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
 * @brief Check if a string contains only digit characters.
 * @return 1 if numeric string, 0 on invalid character
 */
int	is_str_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (printf(ERR_INVALID_COLOR, str), 0);
	}
	return (1);
}

/**
 * @brief Convert an RGB array of strings to a packed 24-bit color.
 * @return Integer representing the RGB color
 */
_int32_t	rgb_from_split(char **split)
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

/**
 * @brief Identify the prefix of a line and return its corresponding flag.
 * @return Bit flag corresponding to the line prefix
 */
uint32_t	get_prefix(char *line)
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
		if (ft_strncmp(tmp, args[i], size) == 0)
			break ;
	}
	if (i >= 6)
		return (printf(ERR_INVALID_HEADER_CHAR, tmp), 0);
	return (1 << i);
}
