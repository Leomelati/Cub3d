/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 09:42:39 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/08 01:55:38 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Swap the value of two floats
*/

void	ft_swap(float *a, float *b)
{
	int aux;

	aux = *a;
	*a = *b;
	*b = aux;
}