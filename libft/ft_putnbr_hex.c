/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 01:51:16 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/07 07:07:19 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Converts an integer of base 10 into a hexadecimal base.
** Prints the result in uppercase.
*/

void	ft_putnbr_hex(size_t nbr)
{
	size_t	mod;

	if (nbr > 0)
	{
		mod = nbr % 16;
		if (mod < 10)
			mod += '0';
		else
			mod += 55;
		ft_putnbr_hex(nbr / 16);
		write(1, &mod, 1);
	}
}
