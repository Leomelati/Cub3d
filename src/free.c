/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 22:45:11 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/11 03:16:56 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_map(t_parameters *info)
{
	int		i;
	
	i = 0;
	while (i < info->map->map_y && info->map->map[i])
	{
		free(info->map->map[i]);
		info->map->map[i] = NULL;
		i++;
	}
	if (info->map->map)
	{
		free(info->map->map);
		info->map->map = NULL;
	}
}

void	ft_free_rays(t_parameters *info)
{
	int		i;

	i = 0;
	while (i <= info->map->num_rays)
	{
		if (info->ray[i])
		{
			free(info->ray[i]);
			info->ray[i] = NULL;
		}
		i++;
	}
	free(info->ray);
	info->ray = NULL;
}

void	ft_free_img(t_parameters *info, t_img *img)
{
	if (img)
	{
		mlx_destroy_image(info->mlx, img->img);
		free(img);
		img = NULL;
	}
}

int		destroy_window(t_parameters *info)
{
	int		i;

	ft_free_rays(info);
	ft_free_map(info);
	ft_free_img(info, info->img);
	if (info->win)
		mlx_destroy_window(info->mlx, info->win);
	free(info->mlx);
	exit(0);
	return (0);
}
