/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 07:45:59 by lmartins          #+#    #+#             */
/*   Updated: 2021/02/11 08:04:33 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	compare_distance(t_ray *ray)
{
	if (ray->horizontal_distance < ray->vertical_distance)
	{
		ray->collision_x = ray->horz_collision_x;
		ray->collision_y = ray->horz_collision_y;
		ray->distance = ray->horizontal_distance;
		ray->vertical_hit = FALSE;
	}
	else
	{
		ray->collision_x = ray->vert_collision_x;
		ray->collision_y = ray->vert_collision_y;
		ray->distance = ray->vertical_distance;
		ray->vertical_hit = TRUE;
	}
}

double	calculate_distance(double x1, double y1, double x2, double y2)
{
	double value;

	value = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return (value);
}

void	facing_position(t_parameters *info, t_ray *ray)
{
	if ((ray->angle > 0 && ray->angle < PI))
		ray->facing_vertical = FRONT;
	else
		ray->facing_vertical = BACK;
	if ((ray->angle < (PI * 0.5)) || (ray->angle > (PI * 1.5)))
		ray->facing_horizontal = RIGHT;
	else
		ray->facing_horizontal = LEFT;
	horizontal_intersection(info, ray);
	vertical_intersection(info, ray);
	compare_distance(ray);
}

void	horizontal_intersection(t_parameters *info, t_ray *ray)
{
	double	xstep;
	double	ystep;
	double	xintercept;
	double	yintercept;
	double	next_touch[2];

	yintercept = floor(info->player->pos_y / info->map->tam_altura) * info->map->tam_altura;
	if (ray->facing_vertical == BACK)
		yintercept += info->map->tam_altura;
	xintercept = info->player->pos_x + ((yintercept - info->player->pos_y) / tan(ray->angle));
	ystep = info->map->tam_altura;
	if (ray->facing_vertical == FRONT)
		ystep *= -1;
	xstep = info->map->tam_altura / tan(ray->angle);
	if (ray->facing_horizontal == LEFT && xstep > 0)
		xstep *= -1;
	else if (ray->facing_horizontal == RIGHT && xstep < 0)
		xstep *= -1;
	next_touch[0] = yintercept;
	next_touch[1] = xintercept;
	if (ray->facing_vertical == FRONT)
		next_touch[0] = next_touch[0] - 1;
	while ((next_touch[1] >= 0) && (next_touch[1] <= info->width) &&
		(next_touch[1] >= 0) && (next_touch[1] <= info->height))
	{
		if (ft_check_wall(next_touch[1], next_touch[0], info))
		{
			ray->horz_collision_y = next_touch[0];
			ray->horz_collision_x = next_touch[1];
			break;
		}
		else
		{
			next_touch[0] += ystep;
			next_touch[1] += xstep;
		}
	}
	if (ray->horz_collision_y == next_touch[0] && ray->horz_collision_x == next_touch[1])
		ray->horizontal_distance = calculate_distance(info->player->pos_x, info->player->pos_y, ray->horz_collision_x, ray->horz_collision_y);
	else
		ray->horizontal_distance = DBL_MAX;
}

void	vertical_intersection(t_parameters *info, t_ray *ray)
{
	double	xstep;
	double	ystep;
	double	xintercept;
	double	yintercept;
	double	next_touch[2];

	xintercept = floor(info->player->pos_x / info->map->tam_largura) * info->map->tam_largura;
	if (ray->facing_horizontal == RIGHT)
		xintercept += info->map->tam_largura;
	yintercept = info->player->pos_y + ((xintercept - info->player->pos_x) * tan(ray->angle));
	xstep = info->map->tam_largura;
	if (ray->facing_horizontal == LEFT)
		xstep *= -1;
	ystep = info->map->tam_largura * tan(ray->angle);
	if (ray->facing_vertical == FRONT && ystep > 0)
		ystep *= -1;
	else if (ray->facing_vertical == BACK && ystep < 0)
		ystep *= -1;
	next_touch[0] = yintercept;
	next_touch[1] = xintercept;
	if (ray->facing_horizontal == LEFT)
		next_touch[1] = next_touch[1] - 1;
	while ((next_touch[1] >= 0) && (next_touch[1] <= info->width) &&
		(next_touch[1] >= 0) && (next_touch[1] <= info->height))
	{
		if (ft_check_wall(next_touch[1], next_touch[0], info))
		{
			ray->vert_collision_y = next_touch[0];
			ray->vert_collision_x = next_touch[1];
			break;
		}
		else
		{
			next_touch[0] += ystep;
			next_touch[1] += xstep;
		}
	}
	if (ray->vert_collision_y == next_touch[0] && ray->vert_collision_x == next_touch[1])
		ray->vertical_distance = calculate_distance(info->player->pos_x, info->player->pos_y, ray->vert_collision_x, ray->vert_collision_y);
	else
		ray->vertical_distance = DBL_MAX;
}

double	normalize_angle(int ray_angle)
{
	ray_angle = ray_angle % (int)(2 * PI);
	if (ray_angle < 0)
		ray_angle = ray_angle + (2 * PI);
	return (ray_angle);
}

void	cast_rays(t_parameters *info)
{
	double	ray_angle;
	int		i;

	ray_angle = info->player->rotation_angle - (info->player->fov / 2);
	i = 0;
	while (i < info->map->num_rays)
	{
		// info->ray[i]->angle = normalize_angle(ray_angle);
		info->ray[i]->angle = ray_angle;
		facing_position(info, info->ray[i]);
		ray_angle += (info->player->fov / info->map->num_rays);
		i++;
	}	
}

void	draw_rays(t_img *img, t_parameters *info)
{
	int		line_start[2];
	int		line_end[2];
	int		i;

	cast_rays(info);
	i = 0;
	while (i < info->map->num_rays)
	{
		line_start[0] = info->player->pos_x + (info->player->size / 2);
		line_start[1] = info->player->pos_y + (info->player->size / 2);
		line_end[0] = line_start[0] + cos(info->ray[i]->angle) * 30;
		line_end[1] = line_start[1] + sin(info->ray[i]->angle) * 30;
		ft_draw_line(img, line_start, line_end, 0x0000FF00);
		i++;
	}
}