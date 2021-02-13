/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 06:51:46 by lmartins          #+#    #+#             */
/*   Updated: 2021/02/13 09:00:23 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_wall(float x, float y, t_parameters *info)
{
	int 	map_index_x;
	int		map_index_y;
	char	letter;

	if (x < 0 || x > info->width || y < 0 || y > info->height)
		return (FALSE);
	map_index_x = floor(x / info->map->tam_largura);
	map_index_y = floor(y / info->map->tam_altura);
	letter = info->map->map[map_index_y][map_index_x];
	if (letter == PATH || ft_strchr(PLAYER_START, letter))
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