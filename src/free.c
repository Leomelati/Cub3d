/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 22:45:11 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/06 07:29:41 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			close_program()
{
	exit(0);
	return (0);
}

void	check_before_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void ft_free_sprites(t_parameters *info)
{
	int i;

	i = 0;
	while (i < info->map->num_sprites)
	{
		free(info->map->sprites_map[i]);
		info->map->sprites_map[i] = NULL;
		i++;
	}
	free(info->map->sprites_map);
	info->map->sprites_map = NULL;
}

void ft_free_rays(t_parameters *info)
{
	int i;

	i = 0;
	while (i < info->map->num_rays)
	{
		check_before_free(info->ray[i]);
		i++;
	}
	free(info->ray);
	info->ray = NULL;
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

int		clean_and_close(t_parameters *info)
{
	info->ray != NULL ? ft_free_rays(info) : 0;
	info->img != NULL ? ft_free_img(info, info->img) : 0;
	info->north_texture != NULL ? ft_free_img(info, info->north_texture) : 0;
	info->south_texture != NULL ? ft_free_img(info, info->south_texture) : 0;
	info->east_texture != NULL ? ft_free_img(info, info->east_texture) : 0;
	info->west_texture != NULL ? ft_free_img(info, info->west_texture) : 0;
	info->sprite_texture != NULL ? ft_free_img(info, info->sprite_texture) : 0;
	info->map->sprites_map != NULL ? ft_free_sprites(info) : 0;
	info->map != NULL ? ft_free_map(info) : 0;
	info->player != NULL ? free(info->player) : 0;
	info->win != NULL ? mlx_destroy_window(info->mlx, info->win) : 0;
	info->mlx != NULL ? ft_free_mlx(info) : 0;
	return (close_program());
}

int		destroy_window(t_parameters *info)
{

	info->ray != NULL ? ft_free_rays(info) : 0;
	info->map->sprites_map != NULL ? ft_free_sprites(info) : 0;
	info->map != NULL ? ft_free_map(info) : 0;
	info->img != NULL ? ft_free_img(info, info->img) : 0;
	info->north_texture != NULL ? ft_free_img(info, info->north_texture) : 0;
	info->south_texture != NULL ? ft_free_img(info, info->south_texture) : 0;
	info->east_texture != NULL ? ft_free_img(info, info->east_texture) : 0;
	info->west_texture != NULL ? ft_free_img(info, info->west_texture) : 0;
	info->sprite_texture != NULL ? ft_free_img(info, info->sprite_texture) : 0;
	info->player != NULL ? free(info->player) : 0;
	info->win != NULL ? mlx_destroy_window(info->mlx, info->win) : 0;
	info->mlx != NULL ? ft_free_mlx(info) : 0;
	return (0);
}
