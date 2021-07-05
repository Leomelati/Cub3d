/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 08:33:42 by lmartins          #+#    #+#             */
/*   Updated: 2021/07/05 08:34:40 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_north(t_parameters *info, int i, t_ray *ray, int *pixel)
{
	t_coordinates	texture;

	texture.x = (int)ray->collision_x % info->north_tex->width;
	texture.y = ((i - pixel[TOP]) * (info->north_tex->height)
			/ (pixel[BOTTOM] - pixel[TOP]));
	return (get_color(info->north_tex, texture.x, texture.y));
}

int	get_texture_south(t_parameters *info, int i, t_ray *ray, int *pixel)
{
	t_coordinates	texture;

	texture.x = (int)ray->collision_x % info->south_tex->width;
	texture.y = ((i - pixel[TOP]) * (info->south_tex->height)
			/ (pixel[BOTTOM] - pixel[TOP]));
	return (get_color(info->south_tex, texture.x, texture.y));
}

int	get_texture_east(t_parameters *info, int i, t_ray *ray, int *pixel)
{
	t_coordinates	texture;

	texture.x = (int)ray->collision_y % info->east_tex->width;
	texture.y = ((i - pixel[TOP]) * (info->east_tex->height)
			/ (pixel[BOTTOM] - pixel[TOP]));
	return (get_color(info->east_tex, texture.x, texture.y));
}

int	get_texture_west(t_parameters *info, int i, t_ray *ray, int *pixel)
{
	t_coordinates	texture;

	texture.x = (int)ray->collision_y % info->west_tex->width;
	texture.y = ((i - pixel[TOP]) * (info->west_tex->height)
			/ (pixel[BOTTOM] - pixel[TOP]));
	return (get_color(info->west_tex, texture.x, texture.y));
}

int	get_texture(t_parameters *info, int i, t_ray *ray, int *pixel)
{
	if (ray->facing_up && !(ray->vertical_hit))
		return (get_texture_north(info, i, ray, pixel));
	else if (ray->facing_down && !(ray->vertical_hit))
		return (get_texture_south(info, i, ray, pixel));
	else if (ray->facing_right && ray->vertical_hit)
		return (get_texture_east(info, i, ray, pixel));
	else if (ray->facing_left && ray->vertical_hit)
		return (get_texture_west(info, i, ray, pixel));
	return (0);
}