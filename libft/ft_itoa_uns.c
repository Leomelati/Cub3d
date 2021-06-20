/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_uns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 07:29:57 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/20 07:26:15 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The regular itoa with a unsigned int parameter
*/

static int	ft_numlen(unsigned int n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa_uns(unsigned int num)
{
	int				len;
	char			*array;

	len = ft_numlen(num) + 1;
	array = (char *)malloc(len * sizeof(char));
	if (!(array))
		return (0);
	array[len - 1] = '\0';
	len -= 2;
	while (num >= 10)
	{
		array[len] = (char)(num % 10) + '0';
		num = num / 10;
		len--;
	}
	array[len] = (char)num % 10 + '0';
	return (array);
}
