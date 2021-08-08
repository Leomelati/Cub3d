/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 22:42:30 by lmartins          #+#    #+#             */
/*   Updated: 2021/08/08 09:58:07 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	define_resolution(t_parameters *info, char *readed)
{
	char	**string;
	int		x;
	int		y;
	int		elements;

	mlx_get_screen_size(info->mlx, &x, &y);
	string = ft_split(readed, ' ');
	elements = 0;
	while (string[elements])
		elements++;
	if (elements == 3)
	{
		if (ft_atoi(string[1]) > x)
			info->width = x;
		else
			info->width = ft_atoi(string[1]);
		if (ft_atoi(string[2]) > y)
			info->height = y;
		else
			info->height = ft_atoi(string[2]);
	}
	if (info->width <= 0 || info->height <= 0)
		ft_error(info, ERROR_SCREEN);
	info->ray = start_rays(info, info->width);
	ft_split_free(string);
}

t_ray	**start_rays(t_parameters *info, int n_rays)
{
	t_ray	**rays;
	int		i;

	info->map->num_rays = n_rays;
	rays = ft_calloc(info->map->num_rays, sizeof(t_ray *));
	i = 0;
	while (i < info->map->num_rays)
	{
		rays[i] = ft_calloc(1, sizeof(t_ray));
		i++;
	}
	info->parsed->rays = TRUE;
	return (rays);
}

void	start_infos(t_parameters *info)
{
	info->map = ft_calloc(1, sizeof(t_map));
	info->player = ft_calloc(1, sizeof(t_player));
	info->img = ft_calloc(1, sizeof(t_img));
	start_player(info->player);
	info->win = NULL;
	info->width = MISS;
	info->height = MISS;
	info->floor_color = MISS;
	info->ceil_color = MISS;
	info->north_tex = ft_calloc(1, sizeof(t_img));
	info->south_tex = ft_calloc(1, sizeof(t_img));
	info->west_tex = ft_calloc(1, sizeof(t_img));
	info->east_tex = ft_calloc(1, sizeof(t_img));
	info->parsed = ft_calloc(1, sizeof(t_parsed));
	info->mlx = mlx_init();
	if (!info->mlx)
		ft_error(info, ERROR_MLX);
}
