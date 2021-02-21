/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 07:45:59 by lmartins          #+#    #+#             */
/*   Updated: 2021/02/21 09:37:57 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	compare_distance(t_ray *ray)
{
	if (ray->horizontal_distance <= ray->vertical_distance)
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
	float	check_x;
	float	check_y;
	float	check_next_touch_x;
	float	check_next_touch_y;

	yintercept = floor(info->player->pos_y / TILE_SIZE) * TILE_SIZE;
	yintercept += (ray->facing_down == TRUE) ? TILE_SIZE : 0;
	xintercept = info->player->pos_x + ((yintercept - info->player->pos_y) / tan(ray->angle));
	ystep = TILE_SIZE;
	ystep *= (ray->facing_up == TRUE) ? -1 : 1;
	xstep = TILE_SIZE / tan(ray->angle);
	xstep *= ((ray->facing_left == TRUE) && (xstep > 0)) ? -1 : 1;
	xstep *= ((ray->facing_right == TRUE) && (xstep < 0)) ? -1 : 1;
	check_y = yintercept;
	check_x = xintercept;
	while ((check_x >= 0) && (check_x <= info->width) &&
		(check_y >= 0) && (check_y <= info->height))
	{

		check_next_touch_x = check_x;
		check_next_touch_y = check_y + (ray->facing_up == TRUE ? -1 : 0);
		if (ft_check_wall(check_next_touch_x, check_next_touch_y, info))
		{
			ray->horz_collision_y = check_next_touch_y;
			ray->horz_collision_x = check_next_touch_x;
			break;
		}
		else
		{
			check_y += ystep;
			check_x += xstep;
		}
	}
	if (ray->horz_collision_y == check_next_touch_y && ray->horz_collision_x == check_next_touch_x)
		ray->horizontal_distance = calculate_distance(info->player->pos_x, info->player->pos_y, ray->horz_collision_x, ray->horz_collision_y);
	else
		ray->horizontal_distance = INT_MAX;
}

void	vertical_intersection(t_parameters *info, t_ray *ray)
{
	float	xstep;
	float	ystep;
	float	xintercept;
	float	yintercept;
	float	check_x;
	float	check_y;
	float	check_next_touch_x;
	float	check_next_touch_y;
	int		line_start[2];
	int		line_end[2];

	xintercept = floor(info->player->pos_x / TILE_SIZE) * TILE_SIZE;
	xintercept += (ray->facing_right == TRUE) ? TILE_SIZE : 0;
	yintercept = info->player->pos_y + ((xintercept - info->player->pos_x) * tan(ray->angle));
	xstep = TILE_SIZE;
	xstep *= (ray->facing_left == TRUE) ? -1 : 1;
	ystep = TILE_SIZE * tan(ray->angle);
	ystep *= ((ray->facing_up == TRUE) && (ystep > 0)) ? -1 : 1;
	ystep *= ((ray->facing_down == TRUE) && (ystep < 0)) ? -1 : 1;
	check_y = yintercept;
	check_x = xintercept;
	while ((check_x >= 0) && (check_x <= info->width) &&
		(check_y >= 0) && (check_y <= info->height))
	{
		check_next_touch_y = check_y;
		check_next_touch_x = check_x + (ray->facing_left == TRUE ? -1 : 0);
		if (ft_check_wall(check_next_touch_x, check_next_touch_y, info))
		{
			ray->vert_collision_y = check_y;
			ray->vert_collision_x = check_x;
			break;
		}
		else
		{
			check_y += ystep;
			check_x += xstep;
		}
	}
	if (ray->vert_collision_y == check_y && ray->vert_collision_x == check_x)
		ray->vertical_distance = calculate_distance(info->player->pos_x, info->player->pos_y, ray->vert_collision_x, ray->vert_collision_y);
	else
		ray->vertical_distance = INT_MAX;
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
		info->ray[i]->angle = normalize_angle(ray_angle);
		facing_position(info, info->ray[i]);
		ray_angle += (info->player->fov / info->map->num_rays);
		i++;
	}	
}

void	wall_limits(t_img *img, t_parameters *info, float wall_height, int column_id)
{
	int		top_pixel;
	int		bottom_pixel;
	int		i;

	top_pixel = (info->height / 2) - (wall_height / 2);
	top_pixel = (top_pixel < 0) ? 0 : top_pixel;
	i = 0;
	while (i < top_pixel)
	{
		ft_pixel_put(img, column_id, i, 0x000000FF);
		i++;
	}
	bottom_pixel = (info->height / 2) + (wall_height / 2);
	bottom_pixel = (bottom_pixel > info->height) ? info->height : bottom_pixel;
	i = bottom_pixel;
	while (i < info->height)
	{
		ft_pixel_put(img, column_id, i, 0x0054FFA3);
		i++;
	}
}

void	draw_rays(t_img *img, t_parameters *info)
{
	float	dist_proj_plan;
	float	wall_proj_height;
	int		line_start[2];
	int		line_end[2];
	int		i;

	cast_rays(info);
	dist_proj_plan = (info->width / 2) / tan(info->player->fov / 2);
	i = 0;
	while (i < info->map->num_rays)
	{
		wall_proj_height = (TILE_SIZE / info->ray[i]->distance) * dist_proj_plan;
		wall_limits(img, info, wall_proj_height, i);
		line_start[0] = i + 1;
		line_start[1] = (info->width / 2) - (wall_proj_height / 2);
		line_start[1] = (line_start[1] > info->height) ? info->height : line_start[1];
		line_start[1] = (line_start[1] < 0) ? 0 : line_start[1];
		line_end[0] = i + 1;
		line_end[1] = line_start[1] + wall_proj_height;
		line_end[1] = (line_end[1] > info->height) ? info->height : line_end[1];
		line_end[1] = (line_end[1] < 0) ? 0 : line_end[1];
		ft_draw_line(img, line_start, line_end, 0x00FF0000);
		i++;
	}
}
