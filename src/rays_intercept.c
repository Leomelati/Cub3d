/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_intercept.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 04:27:47 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/07 04:51:48 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_hoz_intersection(t_coordinates *check, t_coordinates *step,
	t_parameters *info, t_ray *ray)
{
	t_coordinates	check_next;

	while (!ft_window_limit(check->x, check->y, info))
	{
		check_next.x = check->x;
		check_next.y = check->y + (ray->facing_up == TRUE ? -1 : 0);
		if (ft_check_wall(check_next.x, check_next.y, info))
		{
			ray->horz_collision_y = check_next.y;
			ray->horz_collision_x = check_next.x;
			break ;
		}
		else
		{
			check->y += step->y;
			check->x += step->x;
		}
	}
}

void	horizontal_intersection(t_parameters *info, t_ray *ray)
{
	t_coordinates	step;
	t_coordinates	intercept;
	t_coordinates	check;

	intercept.y = floor(info->player->pos_y / TILE_SIZE) * TILE_SIZE;
	intercept.y += (ray->facing_down == TRUE) ? TILE_SIZE : 0;
	intercept.x = info->player->pos_x + ((intercept.y - info->player->pos_y) /
		tan(ray->angle));
	step.y = TILE_SIZE;
	step.y *= (ray->facing_up == TRUE) ? -1 : 1;
	step.x = TILE_SIZE / tan(ray->angle);
	step.x *= ((ray->facing_left == TRUE) && (step.x > 0)) ? -1 : 1;
	step.x *= ((ray->facing_right == TRUE) && (step.x < 0)) ? -1 : 1;
	check.y = intercept.y;
	check.x = intercept.x;
	find_hoz_intersection(&check, &step, info, ray);
	if ((check.x >= 0) && (check.x <= info->width) &&
		(check.y >= 0) && (check.y <= info->height))
		ray->horizontal_distance = calculate_distance(info->player->pos_x,
			info->player->pos_y, ray->horz_collision_x, ray->horz_collision_y);
	else
		ray->horizontal_distance = INT_MAX;
}

void	find_vert_intersection(t_coordinates *check, t_coordinates *step,
	t_parameters *info, t_ray *ray)
{
	t_coordinates	check_next;

	while (!ft_window_limit(check->x, check->y, info))
	{
		check_next.y = check->y;
		check_next.x = check->x + (ray->facing_left == TRUE ? -1 : 0);
		if (ft_check_wall(check_next.x, check_next.y, info))
		{
			ray->vert_collision_y = check->y;
			ray->vert_collision_x = check->x;
			break ;
		}
		else
		{
			check->y += step->y;
			check->x += step->x;
		}
	}
}

void	vertical_intersection(t_parameters *info, t_ray *ray)
{
	t_coordinates	step;
	t_coordinates	intercept;
	t_coordinates	check;

	intercept.x = floor(info->player->pos_x / TILE_SIZE) * TILE_SIZE;
	intercept.x += (ray->facing_right == TRUE) ? TILE_SIZE : 0;
	intercept.y = info->player->pos_y + ((intercept.x - info->player->pos_x)
		* tan(ray->angle));
	step.x = TILE_SIZE;
	step.x *= (ray->facing_left == TRUE) ? -1 : 1;
	step.y = TILE_SIZE * tan(ray->angle);
	step.y *= ((ray->facing_up == TRUE) && (step.y > 0)) ? -1 : 1;
	step.y *= ((ray->facing_down == TRUE) && (step.y < 0)) ? -1 : 1;
	check.y = intercept.y;
	check.x = intercept.x;
	find_vert_intersection(&check, &step, info, ray);
	if ((check.x >= 0) && (check.x <= info->width) &&
		(check.y >= 0) && (check.y <= info->height))
		ray->vertical_distance = calculate_distance(info->player->pos_x,
			info->player->pos_y, ray->vert_collision_x, ray->vert_collision_y);
	else
		ray->vertical_distance = INT_MAX;
}
