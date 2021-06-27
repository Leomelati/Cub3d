/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 06:51:46 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/27 08:31:44 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_window_limit(double x, double y, t_parameters *info)
{
	if (x < 0 || x >= info->width * TILE_SIZE
		|| y < 0 || y >= info->height * TILE_SIZE)
		return (TRUE);
	return (FALSE);
}

int	ft_check_wall(double x, double y, t_parameters *info)
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

int	fill_rolls(t_parameters *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->map->map_y && info->map->map[i])
	{
		j = 0;
		while (info->map->map[i][j])
			j++;
		if (j < info->map->map_x)
			info->map->map[i] = ft_strjoin_free(info->map->map[i],
					ft_calloc_char(info->map->map_x - j, '1'));
		i++;
	}
	return (check_parsed_info(info));
}

int	validate_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->map_y)
	{
		j = 0;
		while (j < map->map_x)
		{
			if ((map->map[i][j] == '0' || map->map[i][j] == '2') &&
			((i == 0 || j == 0 || i == map->map_y - 1 || j == map->map_x - 1)
			|| !check_char(map, i, j)))
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

int	get_map_info(t_parameters *info, char *line, int *row, int *ismap)
{
	int	n_col;
	int	i;

	*ismap = TRUE;
	i = *row;
	n_col = 0;
	info->map->map = (char **)allocate_dynamic((void **)info->map->map,
			sizeof(char *), i);
	n_col = parse_row_map(info, line, info->map->map_y);
	if (!(n_col) || n_col < 0)
	{
		free(line);
		return (n_col);
	}
	if (n_col > info->map->map_x)
		info->map->map_x = n_col;
	else
		info->map->map_x = info->map->map_x;
	info->map->map_y++;
	i++;
	*row = i;
	return (n_col);
}
