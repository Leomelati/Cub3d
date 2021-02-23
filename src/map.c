/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 06:51:46 by lmartins          #+#    #+#             */
/*   Updated: 2021/02/23 06:53:24 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_window_limit(float x, float y, t_parameters *info)
{
	if (x < 0 || x >= info->width || y < 0 || y >= info->height)
		return (TRUE);
	return (FALSE);
}

int		ft_check_wall(float x, float y, t_parameters *info)
{
	int 	map_index_x;
	int		map_index_y;
	char	letter;

	if (ft_window_limit(x, y, info))
		return (TRUE);
	map_index_x = floor(x / TILE_SIZE);
	map_index_y = floor(y / TILE_SIZE);
	if (map_index_x >= info->map->mapX || map_index_y >= info->map->mapY)
		return (TRUE);
	letter = info->map->map[map_index_y][map_index_x];
	if (letter == WALL)
		return (TRUE);
	return (FALSE);
}

void	draw2dMap(t_img	*img, t_parameters *info)
{
	int		x, color;
	int		y = 0;
	char	letter;

	while (y < info->map->mapY)
	{
		x = 0;
		while (x < info->map->mapX)
		{
			letter = info->map->map[y][x];
			if(letter == WALL)
				color = 0x00000000;
			else if(letter == PATH || (ft_strchr(PLAYER_START, letter)))
				color = 0x00FFFFFF;
			else if(letter == EMPTY)
				color = 0x00808080;
			int i = 0;
			while (i < TILE_SIZE)
			{
				int j = 0;
				while (j < TILE_SIZE)
				{
					ft_pixel_put(img, (x * TILE_SIZE) + j, (y * TILE_SIZE) + i, color);
					j++;
				}
				i++;
			}
			x++;
		}
		y++;
	}
}