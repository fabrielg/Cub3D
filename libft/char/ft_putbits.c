/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:00:56 by gfrancoi          #+#    #+#             */
/*   Updated: 2024/11/18 15:57:11 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Print the given bits (char size).
 */
void	ft_putbits(unsigned char bits)
{
	int				i;
	unsigned char	mask;

	i = -1;
	mask = 0b10000000;
	while (++i < (int)(sizeof(unsigned char) * 8))
	{
		ft_putchar_fd((!!(mask & bits)) + '0', STDOUT_FILENO);
		mask >>= 1;
	}
	write(STDOUT_FILENO, "\n", 1);
}
