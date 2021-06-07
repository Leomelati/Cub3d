/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 00:16:27 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/07 07:06:37 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	ssize_t	len1;
	ssize_t	len2;
	char	*strjoin;

	if (!s1 || !s1)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	strjoin = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!(strjoin))
		return (NULL);
	ft_memcpy(strjoin, s1, len1);
	ft_memcpy(&strjoin[len1], s2, len2);
	strjoin[len1 + len2] = '\0';
	free(s1);
	free(s2);
	return (strjoin);
}
