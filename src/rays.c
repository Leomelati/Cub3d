/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 07:45:59 by lmartins          #+#    #+#             */
/*   Updated: 2021/02/12 08:54:52 by lmartins         ###   ########.fr       */
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
		ray->hit_content = ray->horz_hit_content;
		ray->vertical_hit = FALSE;
	}
	else
	{
		ray->collision_x = ray->vert_collision_x;
		ray->collision_y = ray->vert_collision_y;
		ray->distance = ray->vertical_distance;
		ray->hit_content = ray->vert_hit_content;
		ray->vertical_hit = TRUE;
	}
}

float	calculate_distance(float x1, float y1, float x2, float y2)
{
	float value;

	value = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return (value);
}

void	facing_position(t_parameters *info, t_ray *ray)
{
	ray->facing_down = (ray->angle > 0 && ray->angle < PI) ? TRUE : FALSE;
	ray->facing_up = !(ray->angle > 0 && ray->angle < PI) ? TRUE : FALSE;
	ray->facing_right = ((ray->angle < (0.5 * PI)) || (ray->angle > 1.5 * PI)) ? TRUE : FALSE;
	ray->facing_left = !((ray->angle < (0.5 * PI)) || (ray->angle > 1.5 * PI)) ? TRUE : FALSE;
	horizontal_intersection(info, ray);
	vertical_intersection(info, ray);
	compare_distance(ray);
}

void	horizontal_intersection(t_parameters *info, t_ray *ray)
{
	float	xstep;
	float	ystep;
	float	xintercept;
	float	yintercept;
	float	next_touch[2];
	float	check_next_touch_y;

	yintercept = floor(info->player->pos_y / info->map->tam_altura) * info->map->tam_altura;
	yintercept += (ray->facing_down == TRUE) ? info->map->tam_altura : 0;
	xintercept = info->player->pos_x + ((yintercept - info->player->pos_y) / tan(ray->angle));
	ystep = info->map->tam_altura;
	ystep *= (ray->facing_up == TRUE) ? -1 : 1;
	xstep = info->map->tam_altura / tan(ray->angle);
	xstep *= ((ray->facing_left == TRUE) && (xstep > 0)) ? -1 : 1;
	xstep *= ((ray->facing_right == TRUE) && (xstep < 0)) ? -1 : 1;
	next_touch[0] = yintercept;
	next_touch[1] = xintercept;
	while ((next_touch[1] >= 0) && (next_touch[1] <= info->width) &&
		(next_touch[0] >= 0) && (next_touch[0] <= info->height))
	{
		check_next_touch_y = (ray->facing_up == TRUE) ? next_touch[0] - 1 : next_touch[0];
		if (!ft_check_wall(next_touch[1], check_next_touch_y, info))
		{
			ray->horz_collision_y = next_touch[0];
			ray->horz_collision_x = next_touch[1];
			ray->horz_hit_content = info->map->map[(int)floor(check_next_touch_y / info->map->tam_altura)][(int)floor(next_touch[1] / info->map->tam_largura)];
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
		ray->horizontal_distance = FLT_MAX;
}

void	vertical_intersection(t_parameters *info, t_ray *ray)
{
	float	xstep;
	float	ystep;
	float	xintercept;
	float	yintercept;
	float	next_touch[2];
	float	check_next_touch_x;

	xintercept = floor(info->player->pos_x / info->map->tam_largura) * info->map->tam_largura;
	xintercept += (ray->facing_right == TRUE) ? info->map->tam_largura : 0;
	yintercept = info->player->pos_y + ((xintercept - info->player->pos_x) * tan(ray->angle));
	xstep = info->map->tam_largura;
	xstep *= (ray->facing_left == TRUE) ? -1 : 1;
	ystep = info->map->tam_largura * tan(ray->angle);
	ystep *= ((ray->facing_up == TRUE) && (ystep > 0)) ? -1 : 1;
	ystep *= ((ray->facing_down == TRUE) && (ystep < 0)) ? -1 : 1;
	next_touch[0] = yintercept;
	next_touch[1] = xintercept;
	while ((next_touch[1] >= 0) && (next_touch[1] <= info->width) &&
		(next_touch[0] >= 0) && (next_touch[0] <= info->height))
	{
		check_next_touch_x = (ray->facing_left == TRUE) ? next_touch[1] - 1 : next_touch[1];
		printf("Vou testar o next_x: = %f\n Vou testar o y = %f\n", check_next_touch_x, next_touch[0]);
		if (!ft_check_wall(check_next_touch_x, next_touch[0], info))
		{
			printf("Entrei no if vertical!\n");
			ray->horz_collision_y = next_touch[0];
			ray->horz_collision_x = next_touch[1];
			ray->vert_hit_content = info->map->map[(int)floor(next_touch[0] / info->map->tam_altura)][(int)floor(check_next_touch_x / info->map->tam_largura)];
			break;
		}
		else
		{
			printf("Entrei no else vertical!\n");
			next_touch[0] += ystep;
			next_touch[1] += xstep;
		}
	}
	printf("SAi do while!\n");
	if (ray->vert_collision_y == next_touch[0] && ray->vert_collision_x == next_touch[1])
		ray->vertical_distance = calculate_distance(info->player->pos_x, info->player->pos_y, ray->vert_collision_x, ray->vert_collision_y);
	else
		ray->vertical_distance = FLT_MAX;
}

float	normalize_angle(float ray_angle)
{
	ray_angle = remainder(ray_angle, (2 * PI));
	if (ray_angle < 0)
		ray_angle = ray_angle + (2 * PI);
	return (ray_angle);
}

void	cast_rays(t_parameters *info)
{
	float	ray_angle;
	int		i;

	ray_angle = info->player->rotation_angle - (info->player->fov / 2);
	i = 0;
	while (i < info->map->num_rays)
	{
		printf("Entrando raio = %d de %d\n", i, info->map->num_rays);
		info->ray[i]->angle = normalize_angle(ray_angle);
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
		line_start[0] = info->player->pos_x;
		line_start[1] = info->player->pos_y;
		line_end[0] = info->ray[i]->collision_x;
		line_end[1] = info->ray[i]->collision_y;
		ft_draw_line(img, line_start, line_end, 0x00FF0000);
		i++;
	}
}