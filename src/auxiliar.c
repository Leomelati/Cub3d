/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 04:56:35 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/06 03:01:23 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		convert_color(char *readed, t_parameters *info)
{
	char	**string;
	int 	numbers[3];
	int i;

	while (ft_isdigit(*readed))
		readed++;
	string = ft_split(readed, ',');
	printf("Readed: %s\n", readed);
	printf("String[0]: %s\n", string[0]);
	printf("String[1]: %s\n", string[1]);
	printf("String[2]: %s\n", string[2]);
	numbers[0] = ft_atoi(string[0]);
	numbers[1] = ft_atoi(string[1]);
	numbers[2] = ft_atoi(string[2]);
	if (numbers[0] > 255 || numbers[0] < 0)
		define_error_message(1, info);
	if (numbers[1] > 255 || numbers[1] < 0)
		define_error_message(1, info);
	if (numbers[2] > 255 || numbers[2] < 0)
		define_error_message(1, info);
	free(string);
	return (numbers[0] << 16 | numbers[1] << 8 | numbers[2]);
}