/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 04:56:35 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/05 05:40:41 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		convert_color(char *readed, t_parameters *info)
{
	char	**string;
	int 	numbers[3];
	int i;

	string = ft_split(readed, ',');
	numbers[0] = ft_atoi(string[0]);
	numbers[1] = ft_atoi(string[1]);
	numbers[2] = ft_atoi(string[2]);
	free(string);
	return (numbers[0] << 16 | numbers[1] << 8 | numbers[2]);
}