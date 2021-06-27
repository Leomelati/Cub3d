/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 09:42:39 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/27 08:31:44 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Swap the value of two doubles
*/

void	ft_swap(double *a, double *b)
{
	int	aux;

	aux = *a;
	*a = *b;
	*b = aux;
}
