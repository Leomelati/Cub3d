/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 07:45:59 by lmartins          #+#    #+#             */
/*   Updated: 2021/02/02 07:57:16 by lmartins         ###   ########.fr       */
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