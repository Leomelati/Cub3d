/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 08:05:31 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/27 08:54:44 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_map_sprites(t_parameters *info)
{
	int	i;

	i = 0;
	while (i <= info->map->n_sprites)
	{
		free(info->map->sprites_map[i]);
		info->map->sprites_map[i] = NULL;
		i++;
	}
	free(info->map->sprites_map);
	info->map->sprites_map = NULL;
}

void	ft_free_rays(t_parameters *info)
{
	int	i;

	i = 0;
	while (i < info->map->num_rays)
	{
		free(info->ray[i]);
		info->ray[i] = NULL;
		i++;
	}
	free(info->ray);
	info->ray = NULL;
}

void	ft_free_map(t_parameters *info)
{
	int	i;

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
	free(info->map);
	info->map = NULL;
}

void	ft_free_img(t_parameters *info, t_img *img)
{
	if (img)
	{
		mlx_destroy_image(info->mlx, img->img);
		img->img = NULL;
		free(img);
		img = NULL;
	}
}

void	ft_free_mlx(t_parameters *info)
{
	if (info->mlx)
	{
		mlx_destroy_display(info->mlx);
		free(info->mlx);
		info->mlx = NULL;
	}
}
