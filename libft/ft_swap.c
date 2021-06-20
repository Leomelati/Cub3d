/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 09:42:39 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/20 07:10:14 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Swap the value of two floats
*/

void	ft_swap(float *a, float *b)
{
	int	aux;

	aux = *a;
	*a = *b;
	*b = aux;
}
