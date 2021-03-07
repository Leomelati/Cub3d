/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 22:45:11 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/06 22:47:03 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int i;
	ft_free_img(info, info->img);
	if (info->win)
		mlx_destroy_window(info->mlx, info->win);
	// if (info->player)
		// free(info->player);
	if (info->map)
		free(info->map);
	if (info->ray)
	{
		i = 0;
		while (i <= info->map->num_rays)
		{
			free(info->ray[i]);
			i++;
		}
		free(info->ray);
	}
	exit(0);
	return (0);
}