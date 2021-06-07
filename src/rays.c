/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 07:45:59 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/07 06:38:48 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	compare_distance(t_parameters *info, int ray_id)
{
	if (info->ray[ray_id]->hor_distance
		<= info->ray[ray_id]->vert_distance)
	{
		info->ray[ray_id]->collision_x = info->ray[ray_id]->horz_coll_x;
		info->ray[ray_id]->collision_y = info->ray[ray_id]->horz_coll_y;
		info->ray[ray_id]->distance = info->ray[ray_id]->hor_distance;
		info->ray[ray_id]->vertical_hit = FALSE;
	}
	else
	{
		info->ray[ray_id]->collision_x = info->ray[ray_id]->vert_coll_x;
		info->ray[ray_id]->collision_y = info->ray[ray_id]->vert_coll_y;
		info->ray[ray_id]->distance = info->ray[ray_id]->vert_distance;
		info->ray[ray_id]->vertical_hit = TRUE;
	}
}

void	facing_position(t_parameters *info, t_ray *ray)
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
	horizontal_intersection(info, ray);
	vertical_intersection(info, ray);
}

void	cast_all_rays(t_parameters *info)
{
	float	dist_proj_plan;
	float	wall_proj_height;
	float	fixed_dist;
	int		i;

	dist_proj_plan = (info->width / 2) / tan((info->player->fov / 2));
	i = 0;
	while (i < info->map->num_rays)
	{
		info->ray[i]->angle = info->player->rot_angle
			+ atan2((i - info->map->num_rays / 2), dist_proj_plan);
		info->ray[i]->angle = normalize_angle(info->ray[i]->angle);
		facing_position(info, info->ray[i]);
		compare_distance(info, i);
		fixed_dist = info->ray[i]->distance * cos(info->ray[i]->angle
				- info->player->rot_angle);
		wall_proj_height = TILE_SIZE / fixed_dist * dist_proj_plan;
		wall_limits(info, wall_proj_height, i);
		i++;
	}
}
