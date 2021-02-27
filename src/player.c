/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 06:41:50 by lmartins          #+#    #+#             */
/*   Updated: 2021/02/27 09:11:01 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_start_angle(char letter, t_player *player)
{
	if (letter == SOUTH)
		player->rotation_angle = PI / 2;
	else if (letter == NORTH)
		player->rotation_angle = (3 * PI) / 2;
	else if (letter == WEST)
		player->rotation_angle = PI;
	else if (letter == EAST)
		player->rotation_angle = 0;
}

void	player_start_position(t_parameters *info, t_player *player)
{
	int		index_x;
	int		index_y;
	char	letter;
	
	index_y = 0;
	while (index_y < info->map->mapY)
	{
		index_x = 0;
		while (index_x < info->map->mapX)
		{
			letter = info->map->map[index_y][index_x];
			if (ft_strchr(PLAYER_START, letter))
			{
				player->pos_x = floor(index_x * TILE_SIZE);
				player->pos_y = floor(index_y * TILE_SIZE);
				player_start_angle(letter, player);
			}
			index_x++;
		}
		index_y++;
	}
}

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

void	ft_update_player(int keycode, t_parameters *info)
{
	float		move_step;
	int			next_x;
	int			next_y;

	if (keycode == KEY_ARROW_LEFT || keycode == KEY_ARROW_RIGHT)
	{
		info->player->rotation_angle += info->player->turn_direction * info->player->rotation_speed;
		info->player->rotation_angle = normalize_angle(info->player->rotation_angle);
	}
	else
	{
		move_step = info->player->walk_direction * info->player->move_speed;
		next_x = info->player->pos_x;
		next_y = info->player->pos_y;
		if (keycode == KEY_W || keycode == KEY_S)
		{
			next_x += cos(info->player->rotation_angle) * move_step;
			next_y += sin(info->player->rotation_angle) * move_step;
		}
		else
		{
			next_x += cos(info->player->rotation_angle + (PI/2)) * move_step;
			next_y += sin(info->player->rotation_angle + (PI/2)) * move_step;
		}
		if (!ft_check_wall(next_x, next_y, info))
		{
			info->player->pos_x = next_x;
			info->player->pos_y = next_y;
		}
	}
	
}