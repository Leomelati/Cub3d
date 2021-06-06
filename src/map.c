/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 06:51:46 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/06 08:43:44 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_window_limit(float x, float y, t_parameters *info)
{
	if (x < 0 || x >= info->width * TILE_SIZE
		|| y < 0 || y >= info->height * TILE_SIZE)
		return (TRUE);
	return (FALSE);
}

int	ft_check_wall(float x, float y, t_parameters *info)
{
	int		map_index_x;
	int		map_index_y;
	char	letter;

	if (ft_window_limit(x, y, info))
		return (TRUE);
	map_index_x = floor(x / TILE_SIZE);
	map_index_y = floor(y / TILE_SIZE);
	if (map_index_x >= info->map->map_x || map_index_y >= info->map->map_y)
		return (TRUE);
	letter = info->map->map[map_index_y][map_index_x];
	if (letter == WALL)
		return (TRUE);
	return (FALSE);
}
