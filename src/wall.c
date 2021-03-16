/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 04:39:43 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/16 05:36:16 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_color(t_img *img, int x, int y)
{
	char	*color;

	color =  img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)(color));
}

int		get_texture(t_parameters *info, int i, int column_id, int top_pixel, int bottom_pixel)
{
	t_coordinates	texture;

	if (info->ray[column_id]->facing_up && !(info->ray[column_id]->vertical_hit))
	{
		texture.x = (int)info->ray[column_id]->collision_x % info->north_texture->width;
		texture.y = ((i - top_pixel) * (info->north_texture->height) / (bottom_pixel - top_pixel));
		return (get_color(info->north_texture, texture.x, texture.y));
	}
	else if (info->ray[column_id]->facing_down && !(info->ray[column_id]->vertical_hit))
	{
		texture.x = (int)info->ray[column_id]->collision_x % info->south_texture->width;
		texture.y = ((i - top_pixel) * (info->south_texture->height) / (bottom_pixel - top_pixel));
		return (get_color(info->south_texture, texture.x, texture.y));
	}
	else if (info->ray[column_id]->facing_right && info->ray[column_id]->vertical_hit)
	{
		texture.x = (int)info->ray[column_id]->collision_y % info->east_texture->width;
		texture.y = ((i - top_pixel) * (info->east_texture->height) / (bottom_pixel - top_pixel));
		return (get_color(info->east_texture, texture.x, texture.y));
	}
	else if (info->ray[column_id]->facing_left && info->ray[column_id]->vertical_hit)
	{
		texture.x = (int)info->ray[column_id]->collision_y % info->west_texture->width;
		texture.y = ((i - top_pixel) * (info->west_texture->height) / (bottom_pixel - top_pixel));
		return (get_color(info->west_texture, texture.x, texture.y));
	}
	return (0);
}

void	wall_limits(t_img *img, t_parameters *info,
	float wall_height, int column_id)
{
	int		top_pixel;
	int		bottom_pixel;
	int		i;

	top_pixel = (info->height / 2) - (wall_height / 2);
	bottom_pixel = (info->height / 2) + (wall_height / 2);
	i = 0;
	while (i <= top_pixel)
	{
		ft_pixel_put(img, column_id, i, info->ceilling_color);
		i++;
	}
	while (i <= bottom_pixel)
	{
		ft_pixel_put(img, column_id, i, get_texture(info, i, column_id, top_pixel, bottom_pixel));
		i++;
	}
	while (i <= info->height)
	{
		ft_pixel_put(img, column_id, i, info->floor_color);
		i++;
	}
}
