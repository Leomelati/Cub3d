/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 07:45:59 by lmartins          #+#    #+#             */
/*   Updated: 2021/02/07 10:22:11 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_rays(t_parameters *info)
{
	double	ray_angle;
	int		i;
	int		column_id;

	ray_angle = info->player->rotation_angle - (info->player->fov / 2);
	column_id = 0;
	i = 0;
	while (i < info->rays->num_rays)
	{
		info->rays->rays[i] = ray_angle;
		ray_angle += (info->player->fov / info->rays->num_rays);
		column_id++;
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
	while (i < info->rays->num_rays)
	{
		line_start[0] = info->player->pos_x + (info->player->size / 2);
		line_start[1] = info->player->pos_y + (info->player->size / 2);
		line_end[0] = line_start[0] + cos(info->rays->rays[i]) * 30;
		line_end[1] = line_start[1] + sin(info->rays->rays[i]) * 30;
		ft_draw_line(img, line_start, line_end, 0x0000FF00);
		i++;
	}
}