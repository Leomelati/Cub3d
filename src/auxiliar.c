/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 04:56:35 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/08 05:46:46 by lmartins         ###   ########.fr       */
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

int		is_map_line(char *readed)
{
	int i;

	i = 0;
	while (readed[i] != '\0')
	{
		if (ft_strchr(VALID_MAP_CHARS, readed[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int		print_map(t_parameters *info, int i)
{
	int z;
	int j;

	z = 0;
	while (z <= i)
	{
		j = 0;
		while (j <= info->map->map_x)
		{
			printf("%c", info->map->map[z][j]);
			j++;
		}
		printf("\n");
		z++;
	}
	return (0);
}

float	normalize_angle(float ray_angle)
{
	ray_angle = remainder(ray_angle, (2 * PI));
	if (ray_angle < 0)
		ray_angle = ray_angle + (2 * PI);
	return (ray_angle);
}
