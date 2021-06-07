/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 06:20:35 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/07 06:09:51 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_parameters *info)
{
	if (keycode == KEY_ESC)
		clean_and_close(info);
	else if (keycode == KEY_A)
		info->player->walk_direction = LEFT;
	else if (keycode == KEY_D)
		info->player->walk_direction = RIGHT;
	else if (keycode == KEY_W)
		info->player->walk_direction = FRONT;
	else if (keycode == KEY_S)
		info->player->walk_direction = BACK;
	else if (keycode == KEY_ARROW_LEFT)
		info->player->turn_dir = LEFT;
	else if (keycode == KEY_ARROW_RIGHT)
		info->player->turn_dir = RIGHT;
	ft_update_player(keycode, info);
	ft_run(info);
	return (1);
}

int	key_release(int keycode, t_parameters *info)
{
	if (keycode == KEY_ESC)
		clean_and_close(info);
	else if (keycode == KEY_A)
		info->player->walk_direction = FALSE;
	else if (keycode == KEY_D)
		info->player->walk_direction = FALSE;
	else if (keycode == KEY_W)
		info->player->walk_direction = FALSE;
	else if (keycode == KEY_S)
		info->player->walk_direction = FALSE;
	else if (keycode == KEY_ARROW_LEFT)
		info->player->turn_dir = FALSE;
	else if (keycode == KEY_ARROW_RIGHT)
		info->player->turn_dir = FALSE;
	ft_update_player(keycode, info);
	ft_run(info);
	return (1);
}
