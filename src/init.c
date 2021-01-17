/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 22:42:30 by lmartins          #+#    #+#             */
/*   Updated: 2021/01/17 08:07:54 by lmartins         ###   ########.fr       */
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

void	update_infos(t_parameters *info) // WILL BE REMOVED
{
	info->map->mapX = 15;
	info->map->mapY = 11;
	info->map->tam_altura = info->height / info->map->mapY;
	info->map->tam_largura = info->width / info->map->mapX;
}

t_map	*start_map(t_parameters *info)
{
	t_map *map;
	if (!(map = malloc(sizeof(t_map))))
		return (NULL);
	return (map);
}

int		is_map_line(char *readed)
{
	int i;

	i = 0;
	while(readed[i] != '\0')
	{
		if (ft_strchr(VALID_MAP_CHARS, readed[i]))
			return(TRUE);
		i++;
	}
	return (FALSE);
}

char	**malloc_map(t_parameters *info, char *readed, int line)
{
	char **tmp;
	int i;
	int len;

	len = ft_strlen(readed);
	if (!(tmp = malloc(sizeof(char **) * line)))
		return (NULL);	
	i = 0;
	while (i <= line)
	{
		tmp[i] = malloc(sizeof(char *) * len + 1);
		if (i == line)
			ft_memcpy(tmp[i], readed, len + 1);
		else
			ft_memcpy(tmp[i], info->map->map[i], ft_strlen(info->map->map[i]));
		i++;
	}
	free(info->map->map);
	return (tmp);
}

void	read_infos(int fd, t_parameters *info)
{
	char *readed;
	int i;
	int len;

	i = 0;
	while ((info->valid == TRUE) && (get_next_line(fd, &readed) == 1))
	{
		if (readed[0] == 'R')
			define_resolution(info, readed);
		else if (readed[0] == 'N' && readed[1] == 'O' && readed[2] == ' ')
			info->north_texture = read_image_path(readed, info);  // NOT WORKING YET
		else
		{
			if(is_map_line(readed))
			{
				len = ft_strlen(readed);
				printf("Tamanho linha: %d\n", len);
				printf("Alocando linha: %d\n", i);
				info->map->map = malloc_map(info, readed, i);
				for (int j = 0; j < ft_strlen(readed); j++)
				{
					printf("Alocando coluna: %d\n", j);
					info->map->map[i][j] = 't';
				}
				i++;
			}
		}
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