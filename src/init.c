/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 22:42:30 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/06 08:51:39 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	**start_rays(t_parameters *info)
{
	t_ray	**rays;
	int		i;

	rays = ft_calloc(info->map->num_rays, sizeof(t_ray *));
	i = 0;
	while (i < info->map->num_rays)
	{
		rays[i] = ft_calloc(1, sizeof(t_ray));
		i++;
	}
	return (rays);
}

void	**allocate_new(void **buffer, int size, int line)
{
	void	**new;
	int		i;

	new = ft_calloc(line + 2, size);
	i = 0;
	while (i < line)
	{
		new[i] = buffer[i];
		i++;
	}
	if (line > 0)
		free(buffer);
	return (new);
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
	info->sprite_tex = ft_calloc(1, sizeof(t_img));
	info->mlx = mlx_init();
	if (!info->mlx)
		ft_error(info, ERROR_MLX);
}
