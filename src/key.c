/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 06:20:35 by lmartins          #+#    #+#             */
/*   Updated: 2021/01/05 06:42:40 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int keycode, t_parameters *info, t_img *img)
{
	if (keycode == KEY_ESC)
		destroy_window(info);
	else if (keycode == KEY_A)
		info->player->turn_direction = LEFT;
	else if (keycode == KEY_D)
		info->player->turn_direction = RIGHT;
	else if (keycode == KEY_W)
		info->player->walk_direction = FRONT;
	else if (keycode == KEY_S)
		info->player->walk_direction = BACK;
	ft_update_player(info);
	ft_run(info, img);
	return (1);
}

int		key_release(int keycode, t_parameters *info, t_img *img)
{
	if (keycode == KEY_ESC)
		destroy_window(info);
	else if (keycode == KEY_A)
		info->player->turn_direction = FALSE;
	else if (keycode == KEY_D)
		info->player->turn_direction = FALSE;
	else if (keycode == KEY_W)
		info->player->walk_direction = FALSE;
	else if (keycode == KEY_S)
		info->player->walk_direction = FALSE;
	ft_update_player(info);
	ft_run(info, img);
	return (1);
}