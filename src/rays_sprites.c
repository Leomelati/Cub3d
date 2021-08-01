/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 07:45:59 by lmartins          #+#    #+#             */
/*   Updated: 2021/07/27 08:55:36 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	facing_sprite_position(t_parameters *info, t_ray *ray)
{
	if (ray->angle > 0 && ray->angle < PI)
	{
		ray->facing_down = TRUE;
		ray->facing_up = FALSE;
	}
	else
	{
		ray->facing_down = FALSE;
		ray->facing_up = TRUE;
	}
	if ((ray->angle < (0.5 * PI)) || (ray->angle > 1.5 * PI))
	{
		ray->facing_right = TRUE;
		ray->facing_left = FALSE;
	}
	else
	{
		ray->facing_right = FALSE;
		ray->facing_left = TRUE;
	}
	horizontal_sprite_intersection(info, ray);
	vertical_sprite_intersection(info, ray);
}

void	cast_all_sprite_rays(t_parameters *info)
{
	double	dist_proj_plan;
	double	spr_proj_height;
	double	fixed_dist;
	int		i;

	dist_proj_plan = (info->width / 2) / tan((info->player->fov / 2));
	i = 0;
	while (i < info->map->num_rays)
	{
		info->ray[i]->angle = info->player->rot_angle
			+ atan2((i - info->map->num_rays / 2), dist_proj_plan);
		info->ray[i]->angle = normalize_angle(info->ray[i]->angle);
		facing_sprite_position(info, info->ray[i]);
		compare_distance(info, i);
		fixed_dist = info->ray[i]->distance * cos(info->ray[i]->angle
				- info->player->rot_angle);
		spr_proj_height = TILE_SIZE / fixed_dist * dist_proj_plan;
		if (info->ray[i]->content == SPRITE)
			sprite_limits(info, spr_proj_height, i);
		i++;
	}
}
