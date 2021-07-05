/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 04:39:43 by lmartins          #+#    #+#             */
/*   Updated: 2021/07/05 08:34:34 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(t_img *img, int x, int y)
{
	char	*color;

	color = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)(color));
}

void	wall_limits(t_parameters *info, double wall_height, int column_id)
{
	int	pixel[2];
	int	i;

	pixel[TOP] = (info->height / 2) - (wall_height / 2);
	pixel[BOTTOM] = (info->height / 2) + (wall_height / 2);
	i = 0;
	while (i <= pixel[TOP] && i >= 0 && i <= info->height)
	{
		ft_pixel_put(info->img, column_id, i, info->ceil_color);
		i++;
	}
	while (i <= pixel[BOTTOM] && i >= 0 && i <= info->height)
	{
		ft_pixel_put(info->img, column_id, i,
			get_texture(info, i, info->ray[column_id], pixel));
		i++;
	}
	while (i <= info->height)
	{
		ft_pixel_put(info->img, column_id, i, info->floor_color);
		i++;
	}
}
