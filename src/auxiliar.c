/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 04:56:35 by lmartins          #+#    #+#             */
/*   Updated: 2021/08/08 09:32:22 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	**allocate_dynamic(void **buffer, int size, int m)
{
	void	**new_buffer;
	int		i;

	new_buffer = ft_calloc(m + 2, size);
	i = 0;
	while (i < m)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	if (m > 0)
		free(buffer);
	return (new_buffer);
}

int	check_char(t_map *map, int i, int j)
{
	if (i > 0 && i < (map->map_y - 1) && j > 0 && j < (map->map_x - 1))
	{
		if (!(ft_strchr("01", map->map[i - 1][j - 1])) ||
			!(ft_strchr("01", map->map[i][j - 1])) ||
			!(ft_strchr("01", map->map[i + 1][j - 1])) ||
			!(ft_strchr("01", map->map[i - 1][j])) ||
			!(ft_strchr("01", map->map[i + 1][j])) ||
			!(ft_strchr("01", map->map[i - 1][j + 1])) ||
			!(ft_strchr("01", map->map[i][j + 1])) ||
			!(ft_strchr("01", map->map[i + 1][j + 1])))
			return (FALSE);
	}
	return (TRUE);
}

int	convert_color(char *readed, t_parameters *info)
{
	char	**string;
	char	*temp;
	int		numbers[3];

	string = ft_split(readed, ',');
	temp = string[0];
	while (!ft_isdigit(*temp) && *temp != '-')
		temp++;
	numbers[0] = ft_atoi(temp);
	numbers[1] = ft_atoi(string[1]);
	numbers[2] = ft_atoi(string[2]);
	if (numbers[0] > 255 || numbers[0] < 0)
		ft_error(info, ERROR_COLOR);
	if (numbers[1] > 255 || numbers[1] < 0)
		ft_error(info, ERROR_COLOR);
	if (numbers[2] > 255 || numbers[2] < 0)
		ft_error(info, ERROR_COLOR);
	ft_split_free(string);
	return (numbers[0] << 16 | numbers[1] << 8 | numbers[2]);
}

double	calculate_distance(double x0, double y0, double x1, double y1)
{
	return (sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}

double	normalize_angle(double ray_angle)
{
	ray_angle = remainder(ray_angle, (2 * PI));
	if (ray_angle < 0)
		ray_angle = ray_angle + (2 * PI);
	return (ray_angle);
}
