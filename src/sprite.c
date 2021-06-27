/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 22:06:52 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/27 08:57:21 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_sprites(t_parameters *info)
{
	int			i;

	info->sprites = ft_calloc(info->map->n_sprites + 2, sizeof(t_sprite *));
	i = 0;
	while (i < info->map->n_sprites)
	{
		info->sprites[i] = ft_calloc(1, sizeof(t_sprite));
		info->sprites[i]->pos = ft_calloc(1, sizeof(t_coordinates));
		info->sprites[i]->pos->x = info->map->sprites_map[i]->x * TILE_SIZE + TILE_SIZE / 2;
		info->sprites[i]->pos->y = info->map->sprites_map[i]->y * TILE_SIZE + TILE_SIZE / 2;
		i++;
	}
	ft_free_map_sprites(info);
}
