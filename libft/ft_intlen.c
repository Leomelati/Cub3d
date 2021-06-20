/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 03:28:59 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/20 07:13:30 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Count number of digits in an integer.
*/

size_t	ft_intlen(int num)
{
	unsigned int	cont;

	cont = 0;
	while (num != 0)
	{
		num /= 10;
		++cont;
	}
	return (cont);
}
