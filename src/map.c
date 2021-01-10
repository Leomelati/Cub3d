/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 06:51:46 by lmartins          #+#    #+#             */
/*   Updated: 2021/01/10 07:44:01 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_wall(int x, int y, t_parameters *info)
{
	int map_index_x;
	int map_index_y;
	int **map;

	if (x < 0 || x > info->width || y < 0 || info->height)
		return (TRUE);
	map_index_x = x / info->map->tam_largura;
	map_index_y = y / info->map->tam_altura;
	map = &info->map->map;
	if (map[map_index_y][map_index_x] == WALL)
		return (TRUE);
	return (FALSE);
}

void	draw2dMap(t_img	*img, t_parameters *info)
{
	int x, color;
	int y = 0;
	while (y < info->map->mapY)
	{
		x = 0;
		while (x < info->map->mapX)
		{
			if(ft_check_wall(x, y, info))
				color = 0x00000000;
			else
				color = 0x00FFFFFF;
			int i = 0;
			while (i < info->map->tam_altura)
			{
				int j = 0;
				while (j < info->map->tam_largura)
				{
					ft_pixel_put(img, (x * info->map->tam_largura) + j, (y * info->map->tam_altura) + i, color);
					j++;
				}
				i++;
			}
			x++;
		}
		y++;
	}
}