/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 04:56:35 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/07 04:43:19 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		convert_color(char *readed, t_parameters *info)
{
	char	**string;
	char	*temp;
	int		numbers[3];

	string = ft_split(readed, ',');
	temp = string[0];
	while (!ft_isdigit(*temp))
		temp++;
	numbers[0] = ft_atoi(temp);
	numbers[1] = ft_atoi(string[1]);
	numbers[2] = ft_atoi(string[2]);
	if (numbers[0] > 255 || numbers[0] < 0)
		define_error_message(ERROR_COLOR, info);
	if (numbers[1] > 255 || numbers[1] < 0)
		define_error_message(ERROR_COLOR, info);
	if (numbers[2] > 255 || numbers[2] < 0)
		define_error_message(ERROR_COLOR, info);
	free(string);
	return (numbers[0] << 16 | numbers[1] << 8 | numbers[2]);
}

float	calculate_distance(float x1, float y1, float x2, float y2)
{
	float	value;

	value = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return (value);
}

float	normalize_angle(float ray_angle)
{
	ray_angle = remainder(ray_angle, (2 * PI));
	if (ray_angle < 0)
		ray_angle = ray_angle + (2 * PI);
	return (ray_angle);
}
