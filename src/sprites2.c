/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 04:39:43 by lmartins          #+#    #+#             */
/*   Updated: 2021/07/27 08:36:54 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_sprite_texture(t_parameters *info, int i, t_ray *ray, int *pixel)
{
	t_coordinates	texture;

	texture.x = (int)ray->collision_x % info->sprite_tex->width;
	texture.y = ((i - pixel[TOP]) * (info->sprite_tex->height)
			/ (pixel[BOTTOM] - pixel[TOP]));
	return (get_color(info->sprite_tex, texture.x, texture.y));
}

void	sprite_limits(t_parameters *info, double sprite_height, int column_id)
{
	int	pixel[2];
	int	i;

	pixel[TOP] = (info->height / 2) - (sprite_height / 2);
	pixel[BOTTOM] = (info->height / 2) + (sprite_height / 2);
	i = 0;
	while (i <= pixel[TOP] && i >= 0 && i <= info->height)
	{
		i++;
	}
	while (i <= pixel[BOTTOM] && i >= 0 && i <= info->height)
	{
		ft_pixel_put(info->img, column_id, i,
			get_sprite_texture(info, i, info->ray[column_id], pixel));
		i++;
	}
}
