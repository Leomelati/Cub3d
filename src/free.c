/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 22:45:11 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/02 06:22:27 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			close_program()
{
	exit(0);
	return (0);
}

void ft_free_rays(t_parameters *info)
{
	int i;

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

void	check_before_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

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

int		clean_and_close(t_parameters *info)
{
	info->ray ? ft_free_rays(info) : 0;
	info->img ? ft_free_img(info, info->img) : 0;
	info->north_texture ? ft_free_img(info, info->north_texture) : 0;
	info->south_texture ? ft_free_img(info, info->south_texture) : 0;
	info->east_texture ? ft_free_img(info, info->east_texture) : 0;
	info->west_texture ? ft_free_img(info, info->west_texture) : 0;
	info->map ? ft_free_map(info) : 0;
	info->player ? free(info->player) : 0;
	info->win ? mlx_destroy_window(info->mlx, info->win) : 0;
	info->mlx ? free(info->mlx) : 0;
	return (close_program());

}

int		destroy_window(t_parameters *info)
{

	info->ray ? ft_free_rays(info) : 0;
	info->map ? ft_free_map(info) : 0;
	info->img ? ft_free_img(info, info->img) : 0;
	info->north_texture ? ft_free_img(info, info->north_texture) : 0;
	info->south_texture ? ft_free_img(info, info->south_texture) : 0;
	info->east_texture ? ft_free_img(info, info->east_texture) : 0;
	info->west_texture ? ft_free_img(info, info->west_texture) : 0;
	info->player ? free(info->player) : 0;
	info->win ? mlx_destroy_window(info->mlx, info->win) : 0;
	info->mlx ? free(info->mlx) : 0;
}
