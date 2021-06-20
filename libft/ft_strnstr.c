/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 21:57:22 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/20 07:17:32 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	lit_len;
	size_t	i;

	i = 0;
	lit_len = ft_strlen(little);
	if (*little == '\0')
		return ((char *)big);
	while ((*big != '\0') && (i < len))
	{
		if ((ft_strncmp(big, little, lit_len) == 0) && (i + lit_len <= len))
		{
			return ((char *)big);
		}
		big++;
		i++;
	}
	return (NULL);
}
