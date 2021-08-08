/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 22:45:11 by lmartins          #+#    #+#             */
/*   Updated: 2021/08/08 09:43:54 by lmartins         ###   ########.fr       */
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
	ft_free_img(info, info->north_tex);
	ft_free_img(info, info->south_tex);
	ft_free_img(info, info->east_tex);
	ft_free_img(info, info->west_tex);
	ft_free_map(info);
	free(info->player);
	ft_free_parsed(info);
	mlx_destroy_window(info->mlx, info->win);
	ft_free_mlx(info);
	return (close_program());
}

int	destroy_window(t_parameters *info)
{
	if (info->parsed->rays == TRUE)
		ft_free_rays(info);
	if (info->parsed->img == TRUE)
		ft_free_img(info, info->img);
	if (info->parsed->north_tex == TRUE)
		ft_free_img(info, info->north_tex);
	if (info->parsed->south_tex == TRUE)
		ft_free_img(info, info->south_tex);
	if (info->parsed->east_tex == TRUE)
		ft_free_img(info, info->east_tex);
	if (info->parsed->west_tex == TRUE)
		ft_free_img(info, info->west_tex);
	if (info->parsed->win == TRUE)
		mlx_destroy_window(info->mlx, info->win);
	ft_free_map(info);
	free(info->player);
	ft_free_parsed(info);
	ft_free_mlx(info);
	return (0);
}
