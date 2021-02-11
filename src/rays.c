/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 07:45:59 by lmartins          #+#    #+#             */
/*   Updated: 2021/02/11 05:26:46 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	horizontal_intersection(t_parameters *info, double ray_angle)
{
	double	xstep;
	double	ystep;
	double	xintercept;
	double	yintercept;

	yintercept = floor(info->player->pos_y / info->map->tam_altura) * info->map->tam_altura;
	xintercept = info->player->pos_x + ((yintercept - info->player->pos_y) / tan(ray_angle));
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
	int		distance;
	int		wall_hit_x;
	int		wall_hit_y;

	ray_angle = info->player->rotation_angle - (info->player->fov / 2);
	i = 0;
	while (i < info->map->num_rays)
	{
		info->ray[i]->angle = normalize_angle(ray_angle);
		ray_angle += (info->player->fov / info->map->num_rays);
		wall_hit_x = 0;
		wall_hit_y = 0;
		distance = 0;
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
		line_end[0] = line_start[0] + cos(info->ray[i]->angle) * 60;
		line_end[1] = line_start[1] + sin(info->ray[i]->angle) * 60;
		ft_draw_line(img, line_start, line_end, 0x0000FF00);
		i++;
	}
}