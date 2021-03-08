/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 22:42:30 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/08 01:13:01 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray		**start_rays(t_parameters *info)
{
	t_ray	**rays;
	int		i;

	if (!(rays = malloc(info->map->num_rays * sizeof(t_ray *))))
		return (NULL);
	i = 0;
	while (i <= info->map->num_rays)
	{
		rays[i] = calloc(1, sizeof(t_ray));
		i++;
	}
	return (rays);
}

t_map		*start_map(t_parameters *info)
{
	t_map *map;

	if (!(map = malloc(sizeof(t_map))))
		return (NULL);
	map->map_x = 0;
	map->map_y = 0;
	map->num_rays = 0;
	return (map);
}

char		**malloc_map(t_parameters *info, char *readed, int line)
{
	char	**tmp;
	int		i;
	int		len;

	len = ft_strlen(readed) - 1;
	if (len > info->map->map_x)
		info->map->map_x = len;
	if (!(tmp = malloc(sizeof(char **) * line)))
		return (NULL);
	i = 0;
	while (i <= line)
	{
		tmp[i] = malloc(sizeof(char *) * info->map->map_x + 1);
		if (i == line)
			ft_memcpy(tmp[i], readed, info->map->map_x + 1);
		else
			ft_memcpy(tmp[i], info->map->map[i], ft_strlen(info->map->map[i]));
		i++;
	}
	free(info->map->map);
	return (tmp);
}

void		start_infos(t_parameters *info)
{
	info->mlx = NULL;
	info->win = NULL;
	info->width = MISS;
	info->height = MISS;
	info->floor_color = MISS;
	info->ceilling_color = MISS;
	info->north_texture = NULL;
	info->south_texture = NULL;
	info->west_texture = NULL;
	info->east_texture = NULL;
	info->sprite_texture = NULL;
	info->img = NULL;
	info->map = start_map(info);
}
