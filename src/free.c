/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 22:45:11 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/06 08:18:08 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_program(void)
{
	exit(0);
	return (0);
}

int	clean_and_close(t_parameters *info)
{
	ft_free_rays(info);
	ft_free_img(info, info->img);
	ft_free_img(info, info->north_texture);
	ft_free_img(info, info->south_texture);
	ft_free_img(info, info->east_texture);
	ft_free_img(info, info->west_texture);
	ft_free_img(info, info->sprite_texture);
	ft_free_sprites(info);
	ft_free_map(info);
	free(info->player);
	mlx_destroy_window(info->mlx, info->win);
	ft_free_mlx(info);
	return (close_program());
}

int	destroy_window(t_parameters *info)
{
	ft_free_rays(info);
	ft_free_sprites(info);
	ft_free_map(info);
	ft_free_img(info, info->img);
	ft_free_img(info, info->north_texture);
	ft_free_img(info, info->south_texture);
	ft_free_img(info, info->east_texture);
	ft_free_img(info, info->west_texture);
	ft_free_img(info, info->sprite_texture);
	free(info->player);
	mlx_destroy_window(info->mlx, info->win);
	ft_free_mlx(info);
	return (0);
}
