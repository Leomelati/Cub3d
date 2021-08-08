/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 07:45:59 by lmartins          #+#    #+#             */
/*   Updated: 2021/08/08 09:55:33 by lmartins         ###   ########.fr       */
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
		info->ray[ray_id]->content = info->ray[ray_id]->horz_content;
		info->ray[ray_id]->vertical_hit = FALSE;
	}
	else
	{
		info->ray[ray_id]->collision_x = info->ray[ray_id]->vert_coll_x;
		info->ray[ray_id]->collision_y = info->ray[ray_id]->vert_coll_y;
		info->ray[ray_id]->distance = info->ray[ray_id]->vert_distance;
		info->ray[ray_id]->content = info->ray[ray_id]->vert_content;
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
	double	dist_proj_plan;
	double	wall_proj_height;
	double	fixed_dist;
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

void	define_intercept(t_parameters *info, t_ray *ray,
	t_coordinates	*intercept, int option)
{
	if (option == HOR)
	{
		intercept->y = floor(info->player->pos_y / TILE_SIZE) * TILE_SIZE;
		if (ray->facing_down == TRUE)
			intercept->y += TILE_SIZE;
		intercept->x = info->player->pos_x
			+ ((intercept->y - info->player->pos_y) / tan(ray->angle));
	}
	else
	{
		intercept->x = floor(info->player->pos_x / TILE_SIZE) * TILE_SIZE;
		if (ray->facing_right == TRUE)
			intercept->x += TILE_SIZE;
		intercept->y = info->player->pos_y
			+ ((intercept->x - info->player->pos_x) * tan(ray->angle));
	}
}

void	define_step(t_parameters *info, t_ray *ray,
	t_coordinates	*step, int option)
{
	if (option == HOR)
	{
		step->y = TILE_SIZE;
		if (ray->facing_up == TRUE)
			step->y *= -1;
		step->x = TILE_SIZE / tan(ray->angle);
		if ((ray->facing_left == TRUE) && (step->x > 0))
			step->x *= -1;
		if ((ray->facing_right == TRUE) && (step->x < 0))
			step->x *= -1;
	}
	else
	{
		step->x = TILE_SIZE;
		if (ray->facing_left == TRUE)
			step->x *= -1;
		step->y = TILE_SIZE * tan(ray->angle);
		if ((ray->facing_up == TRUE) && (step->y > 0))
			step->y *= -1;
		if ((ray->facing_down == TRUE) && (step->y < 0))
			step->y *= -1;
	}
}
