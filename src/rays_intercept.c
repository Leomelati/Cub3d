/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_intercept.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 04:27:47 by lmartins          #+#    #+#             */
/*   Updated: 2021/08/07 07:15:03 by lmartins         ###   ########.fr       */
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
		check_next.y = check->y;
		if (ray->facing_up == TRUE)
			check_next.y--;
		if (ft_check_wall(check_next.x, check_next.y, info))
		{
			ray->horz_coll_y = check_next.y;
			ray->horz_coll_x = check_next.x;
			break ;
		}
		else
		{
			check->y += step->y;
			check->x += step->x;
		}
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

void	horizontal_intersection(t_parameters *info, t_ray *ray)
{
	t_coordinates	step;
	t_coordinates	intercept;
	t_coordinates	check;

	define_intercept(info, ray, &intercept, HOR);
	define_step(info, ray, &step, HOR);
	check.y = intercept.y;
	check.x = intercept.x;
	find_hoz_intersection(&check, &step, info, ray);
	if ((check.x >= 0) && (check.x <= info->width * TILE_SIZE)
		&& (check.y >= 0) && (check.y <= info->height * TILE_SIZE))
		ray->hor_distance = calculate_distance(info->player->pos_x,
				info->player->pos_y, ray->horz_coll_x, ray->horz_coll_y);
	else
		ray->hor_distance = INT_MAX;
}

void	find_vert_intersection(t_coordinates *check, t_coordinates *step,
	t_parameters *info, t_ray *ray)
{
	t_coordinates	check_next;

	while (!ft_window_limit(check->x, check->y, info))
	{
		check_next.y = check->y;
		check_next.x = check->x;
		if (ray->facing_left == TRUE)
			check_next.x--;
		if (ft_check_wall(check_next.x, check_next.y, info))
		{
			ray->vert_coll_y = check->y;
			ray->vert_coll_x = check->x;
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

	define_intercept(info, ray, &intercept, VER);
	define_step(info, ray, &step, VER);
	check.y = intercept.y;
	check.x = intercept.x;
	find_vert_intersection(&check, &step, info, ray);
	if ((check.x >= 0) && (check.x <= info->width * TILE_SIZE)
		&& (check.y >= 0) && (check.y <= info->height * TILE_SIZE))
		ray->vert_distance = calculate_distance(info->player->pos_x,
				info->player->pos_y, ray->vert_coll_x, ray->vert_coll_y);
	else
		ray->vert_distance = INT_MAX;
}
