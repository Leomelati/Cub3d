/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 22:42:30 by lmartins          #+#    #+#             */
/*   Updated: 2021/01/10 07:42:58 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	define_resolution(t_parameters *info, char *readed)
{
	char	**string;
	int		x;
	int		y;
	int		elements;

	if ((info->width != MISS) || (info->height != MISS))
		info->valid = FALSE;
	mlx_get_screen_size(info->mlx, &x, &y);
	string = ft_split(readed, ' ');
	elements = 0;
	while (string[elements])
		elements++;
	if (elements == 3)
	{
		info->width = (ft_atoi(string[1]) > x) ? x : ft_atoi(string[1]);
		info->height = (ft_atoi(string[2]) > y) ? y : ft_atoi(string[2]);
	}
	else
		info->valid = FALSE;
	free(string);
}

t_player	*start_player()
{
	t_player *player;
	if (!(player = malloc(sizeof(t_player))))
		return (NULL);
	player->pos_x = 200;
	player->pos_y = 300;
	player->size = 5;
	player->turn_direction = FALSE;
	player->walk_direction = FALSE;
	player->rotation_angle = PI / 2;
	player->move_speed = 2;
	player->rotation_speed = 2 * (PI / 180);
	return (player);
}

t_map	*start_map(t_parameters *info)
{
	t_map *map;
	if (!(map = malloc(sizeof(t_map))))
		return (NULL);
	int mapa[11][15] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	map->map = &mapa;
	map->mapX = 15;
	map->mapY = 11;
	map->tam_altura = info->height / map->mapY;
	map->tam_largura = info->width / map->mapX;
	return (map);
}

void	read_infos(int fd, t_parameters *info)
{
	char *readed;

	while ((info->valid == TRUE) && (get_next_line(fd, &readed) == 1))
	{
		if (readed[0] == 'R')
			define_resolution(info, readed);
		else if (readed[0] == 'N' && readed[1] == 'O' && readed[2] == ' ')
			info->north_texture = read_image_path(readed, info);
	}
	free(readed);
}

void	start_infos(t_parameters *info)
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
	info->valid = TRUE;
	info->player = start_player();
	info->map = start_map(info);
}