/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 07:45:59 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/12 06:22:03 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	compare_distance(t_parameters *info, int ray_id)
{
	if (info->ray[ray_id]->horizontal_distance <=
		info->ray[ray_id]->vertical_distance)
	{
		info->ray[ray_id]->collision_x = info->ray[ray_id]->horz_collision_x;
		info->ray[ray_id]->collision_y = info->ray[ray_id]->horz_collision_y;
		info->ray[ray_id]->distance = info->ray[ray_id]->horizontal_distance;
		info->ray[ray_id]->vertical_hit = FALSE;
	}
	else
	{
		info->ray[ray_id]->collision_x = info->ray[ray_id]->vert_collision_x;
		info->ray[ray_id]->collision_y = info->ray[ray_id]->vert_collision_y;
		info->ray[ray_id]->distance = info->ray[ray_id]->vertical_distance;
		info->ray[ray_id]->vertical_hit = TRUE;
	}
}

void	facing_position(t_parameters *info, t_ray *ray)
{
	ray->facing_down = (ray->angle > 0 && ray->angle < PI) ? TRUE : FALSE;
	ray->facing_up = !(ray->angle > 0 && ray->angle < PI) ? TRUE : FALSE;
	ray->facing_right = ((ray->angle < (0.5 * PI)) ||
		(ray->angle > 1.5 * PI)) ? TRUE : FALSE;
	ray->facing_left = !((ray->angle < (0.5 * PI)) ||
		(ray->angle > 1.5 * PI)) ? TRUE : FALSE;
	horizontal_intersection(info, ray);
	vertical_intersection(info, ray);
}

void	cast_rays(t_parameters *info)
{
	float	ray_angle;
	int		i;

	ray_angle = info->player->rotation_angle - (info->player->fov / 2);
	i = 0;
	while (i < info->map->num_rays)
	{
		info->ray[i]->angle = normalize_angle(ray_angle);
		facing_position(info, info->ray[i]);
		compare_distance(info, i);
		ray_angle += (info->player->fov / info->map->num_rays);
		i++;
	}
}

void	cast_all_rays(t_img *img, t_parameters *info)
{
	float	dist_proj_plan;
	float	wall_proj_height;
	float	fixed_dist;
	int		i;

	cast_rays(info);
	dist_proj_plan = (info->width / 2) / tan(info->player->fov / 2);
	i = 0;
	while (i < info->map->num_rays)
	{
		fixed_dist = info->ray[i]->distance * cos(info->ray[i]->angle
			- info->player->rotation_angle);
		wall_proj_height = (TILE_SIZE / fixed_dist) * dist_proj_plan;
		wall_limits(img, info, wall_proj_height, i);
		i++;
	}
}
