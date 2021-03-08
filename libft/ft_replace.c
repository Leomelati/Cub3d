/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 06:24:46 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/08 06:36:09 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Finds and replace a char on a string
*/

void	ft_replace(char *str, char find, char replace)
{
	char *position;
	position = ft_strchr(str, find);
	while (position)
	{
		*position = replace;
		position = ft_strchr(position, find);
	}
}