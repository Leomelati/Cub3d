/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 22:42:30 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/06 07:06:23 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray		**start_rays(t_parameters *info)
{
	t_ray	**rays;
	int		i;

	if (!(rays = ft_calloc(info->map->num_rays, sizeof(t_ray *))))
		return (NULL);
	i = 0;
	while (i < info->map->num_rays)
	{
		rays[i] = ft_calloc(1, sizeof(t_ray));
		i++;
	}
	return (rays);
}

void		**allocate_new(void **buffer, int size, int line)
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
	(line > 0) ? free(buffer) : 0;
	return (new);
}

void		start_infos(t_parameters *info)
{
	info->map = ft_calloc(1, sizeof(t_map));
	info->player = ft_calloc(1, sizeof(t_player));
	info->img = ft_calloc(1, sizeof(t_img));
	start_player(info->player);
	info->win = NULL;
	info->width = MISS;
	info->height = MISS;
	info->floor_color = MISS;
	info->ceilling_color = MISS;
	info->north_texture = ft_calloc(1, sizeof(t_img));
	info->south_texture = ft_calloc(1, sizeof(t_img));
	info->west_texture = ft_calloc(1, sizeof(t_img));
	info->east_texture = ft_calloc(1, sizeof(t_img));
	info->sprite_texture = ft_calloc(1, sizeof(t_img));
	if (!(info->mlx = mlx_init()))
		ft_error(info, ERROR_MLX);
}
