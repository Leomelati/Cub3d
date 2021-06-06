/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 06:41:50 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/06 06:17:05 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_player(t_player *player)
{
	player->fov = FOV_ANGLE * (PI / 180);
	player->size = 5;
	player->turn_direction = FALSE;
	player->walk_direction = FALSE;
	player->move_speed = 5;
	player->rotation_speed = 5 * (PI / 180);
	player->pos_x = MISS;
	player->pos_y = MISS;
}

int	parse_initial_position(t_parameters *info, char c, int row, int column)
{
	if (info->player->pos_x != MISS || info->player->pos_y != MISS)
		return (ERROR_PLAYER);
	info->player->pos_x = column * TILE_SIZE + 1;
	info->player->pos_y = row * TILE_SIZE + 1;
	info->player->rotation_angle = (c == NORTH) ? (3 * PI) / 2 : 0;
	info->player->rotation_angle = (c == SOUTH) ? PI / 2 : info->player->rotation_angle;
	info->player->rotation_angle = (c == EAST) ? 0 : info->player->rotation_angle;
	info->player->rotation_angle = (c == WEST) ? PI : info->player->rotation_angle;
	info->map->map[row][column] = '0';
	return (0);
}

void		calculate_next_move(int keycode, float move_step,
	t_coordinates *next, t_parameters *info)
{
	next->x = info->player->pos_x;
	next->y = info->player->pos_y;
	if (keycode == KEY_W || keycode == KEY_S)
	{
		next->x += cos(info->player->rotation_angle) * move_step;
		next->y += sin(info->player->rotation_angle) * move_step;
	}
	else
	{
		next->x += cos(info->player->rotation_angle + (PI / 2)) * move_step;
		next->y += sin(info->player->rotation_angle + (PI / 2)) * move_step;
	}
}

void		ft_update_player(int keycode, t_parameters *info)
{
	float			move_step;
	t_coordinates	next;

	if (keycode == KEY_ARROW_LEFT || keycode == KEY_ARROW_RIGHT)
	{
		info->player->rotation_angle +=
			info->player->turn_direction * info->player->rotation_speed;
		info->player->rotation_angle =
			normalize_angle(info->player->rotation_angle);
	}
	else
	{
		move_step = info->player->walk_direction * info->player->move_speed;
		calculate_next_move(keycode, move_step, &next, info);
		if (!ft_check_wall(next.x, next.y, info))
		{
			info->player->pos_x = next.x;
			info->player->pos_y = next.y;
		}
	}
}
