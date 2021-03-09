/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 22:42:30 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/10 00:11:27 by lmartins         ###   ########.fr       */
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

void		malloc_map(t_map *map, char *readed, int line)
{
	char	**tmp;
	int		i;
	int		len;

	len = ft_strlen(readed);
	ft_replace(readed, ' ', '1');
	map->map = (char **)allocate_new((void **)map->map, sizeof(char *), line);
	map->map[line] = readed;
	i = 0;
	while (readed[i])
	{
		map->map[line][i] = readed[i];
		i++;
	}
	if (len > map->map_x)
		map->map_x = len;
	map->map_y++;
}

void		start_infos(t_parameters *info)
{
	info->mlx = mlx_init();
	info->map = ft_calloc(1, sizeof(t_map));
	info->map->map = NULL;
	info->map->map_x = 0;
	info->map->map_y = 0;
	info->map->num_rays = 0;
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
}
