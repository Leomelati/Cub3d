/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 06:41:50 by lmartins          #+#    #+#             */
/*   Updated: 2021/01/22 07:30:45 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_img	*img, t_parameters *info)
{
	int i;
	int j;

	i = 0;
	while (i <= info->player->size)
	{
		j = 0;
		while (j <= info->player->size)
		{
			ft_pixel_put(img, info->player->pos_x + i, info->player->pos_y + j, 0x00FF0000);
			j++;
		}
		i++;
	}
}

void	ft_update_player(t_parameters *info)
{
	double		move_step;
	int			next_x;
	int			next_y;

	info->player->rotation_angle += info->player->turn_direction * info->player->rotation_speed;
	move_step = info->player->walk_direction * info->player->move_speed;
	next_x = info->player->pos_x + cos(info->player->rotation_angle) * move_step;
	next_y = info->player->pos_y + sin(info->player->rotation_angle) * move_step;
	if (ft_check_wall(next_x, next_y, info))
	{
		info->player->pos_x = next_x;
		info->player->pos_y = next_y;
	}
	
}