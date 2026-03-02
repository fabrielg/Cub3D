#include "cub3d.h"
#include "libft.h"

/**
 * @brief Check if a string ends with the given extension.
 * @return 0 if extension matches, 1 otherwise
 */
int	check_extension(char *str, char *ext)
{
	int	i;
	int	str_l;
	int	ext_l;

	str_l = ft_strlen(str);
	ext_l = ft_strlen(ext);
	i = -1;
	if (!str || !ext || str_l < ext_l)
		return (1);
	while (++i < ext_l && str[str_l - ext_l + i])
	{
		if (str[str_l - ext_l + i] != ext[i])
			return (1);
	}
	return (0);
}
