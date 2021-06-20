/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 00:21:03 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/20 07:11:23 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc_char(size_t count, char c)
{
	unsigned char	*ptr;
	size_t			mem;

	mem = count * sizeof(char);
	ptr = malloc(mem + 1);
	if (!(ptr))
		return (NULL);
	ft_memset(ptr, c, mem);
	ptr[mem] = '\0';
	return ((void *)ptr);
}
