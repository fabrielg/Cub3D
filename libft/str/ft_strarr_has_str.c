/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_has_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:04:26 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/12/16 19:14:55 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strarr_has_str(const char **arr, const char *str, int size)
{
	int	i;

	if (!arr || !(*arr))
		return (0);
	i = 0;
	while (i < size || (size < 0 && arr[i]))
	{
		if (ft_strncmp(arr[i], str, -1) == 0)
			return ((char *)arr[i]);
		i++;
	}
	return (NULL);
}
