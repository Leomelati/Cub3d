/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 04:39:43 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/07 06:55:21 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(t_img *img, int x, int y)
{
	char	*color;

	color = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)(color));
}

int	get_texture(t_parameters *info, int i, int column_id,
	int top_pixel, int bottom_pixel)
{
	t_coordinates	texture;

	if (info->ray[column_id]->facing_up
		&& !(info->ray[column_id]->vertical_hit))
	{
		texture.x = (int)info->ray[column_id]->collision_x
			% info->north_tex->width;
		texture.y = ((i - top_pixel) * (info->north_tex->height)
				/ (bottom_pixel - top_pixel));
		return (get_color(info->north_tex, texture.x, texture.y));
	}
	else if (info->ray[column_id]->facing_down
		&& !(info->ray[column_id]->vertical_hit))
	{
		texture.x = (int)info->ray[column_id]->collision_x
			% info->south_tex->width;
		texture.y = ((i - top_pixel) * (info->south_tex->height)
				/ (bottom_pixel - top_pixel));
		return (get_color(info->south_tex, texture.x, texture.y));
	}
	else if (info->ray[column_id]->facing_right
		&& info->ray[column_id]->vertical_hit)
	{
		texture.x = (int)info->ray[column_id]->collision_y
			% info->east_tex->width;
		texture.y = ((i - top_pixel) * (info->east_tex->height)
				/ (bottom_pixel - top_pixel));
		return (get_color(info->east_tex, texture.x, texture.y));
	}
	else if (info->ray[column_id]->facing_left
		&& info->ray[column_id]->vertical_hit)
	{
		texture.x = (int)info->ray[column_id]->collision_y
			% info->west_tex->width;
		texture.y = ((i - top_pixel) * (info->west_tex->height)
				/ (bottom_pixel - top_pixel));
		return (get_color(info->west_tex, texture.x, texture.y));
	}
	return (0);
}

void	wall_limits(t_parameters *info, float wall_height, int column_id)
{
	int		top_pixel;
	int		bottom_pixel;
	int		i;

	top_pixel = (info->height / 2) - (wall_height / 2);
	bottom_pixel = (info->height / 2) + (wall_height / 2);
	i = 0;
	while (i <= top_pixel && i >= 0 && i <= info->height)
	{
		ft_pixel_put(info->img, column_id, i, info->ceil_color);
		i++;
	}
	while (i <= bottom_pixel && i >= 0 && i <= info->height)
	{
		ft_pixel_put(info->img, column_id, i,
			get_texture(info, i, column_id, top_pixel, bottom_pixel));
		i++;
	}
	while (i <= info->height)
	{
		ft_pixel_put(info->img, column_id, i, info->floor_color);
		i++;
	}
}
