/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 06:41:50 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/27 08:31:44 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_player(t_player *player)
{
	player->fov = FOV_ANGLE * (PI / 180);
	player->size = 5;
	player->turn_dir = FALSE;
	player->walk_direction = FALSE;
	player->move_speed = 10;
	player->rot_speed = 5 * (PI / 180);
	player->pos_x = MISS;
	player->pos_y = MISS;
}

int	parse_initial_position(t_parameters *info, char c, int row, int column)
{
	if (info->player->pos_x != MISS || info->player->pos_y != MISS)
		return (ERROR_PLAYER);
	info->player->pos_x = column * TILE_SIZE + 1;
	info->player->pos_y = row * TILE_SIZE + 1;
	if (c == NORTH)
		info->player->rot_angle = (3 * PI) / 2;
	else if (c == SOUTH)
		info->player->rot_angle = PI / 2;
	else if (c == EAST)
		info->player->rot_angle = 0;
	else if (c == WEST)
		info->player->rot_angle = PI;
	info->map->map[row][column] = '0';
	return (0);
}

void	calculate_next_move(int keycode, double move_step,
	t_coordinates *next, t_parameters *info)
{
	next->x = info->player->pos_x;
	next->y = info->player->pos_y;
	if (keycode == KEY_W || keycode == KEY_S)
	{
		next->x += cos(info->player->rot_angle) * move_step;
		next->y += sin(info->player->rot_angle) * move_step;
	}
	else
	{
		next->x += cos(info->player->rot_angle + (PI / 2)) * move_step;
		next->y += sin(info->player->rot_angle + (PI / 2)) * move_step;
	}
}

void	ft_update_player(int keycode, t_parameters *i)
{
	double			move_step;
	t_coordinates	next;

	if (keycode == KEY_ARROW_LEFT || keycode == KEY_ARROW_RIGHT)
	{
		i->player->rot_angle += i->player->turn_dir * i->player->rot_speed;
		i->player->rot_angle = normalize_angle(i->player->rot_angle);
	}
	else
	{
		move_step = i->player->walk_direction * i->player->move_speed;
		calculate_next_move(keycode, move_step, &next, i);
		if (!ft_check_wall(next.x, next.y, i))
		{
			i->player->pos_x = next.x;
			i->player->pos_y = next.y;
		}
	}
}
