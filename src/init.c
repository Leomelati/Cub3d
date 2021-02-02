/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 22:42:30 by lmartins          #+#    #+#             */
/*   Updated: 2021/02/02 07:52:38 by lmartins         ###   ########.fr       */
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

t_rays		*start_rays(t_parameters *info)
{
	t_rays *rays;
	
	if (!(rays = malloc(sizeof(t_rays))))
		return (NULL);
	rays->num_rays = info->width / WALL_WIDTH;
	if (!(rays->rays = malloc(sizeof(double *) * rays->num_rays)))
		return (NULL);
	return(rays);
}

t_player	*start_player(t_parameters *info)
{
	t_player *player;

	if (!(player = malloc(sizeof(t_player))))
		return (NULL);
	player_start_position(info, player);
	player->fov = FOV_ANGLE * (PI / 180);
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
	map->mapX = 0;
	map->mapY = 0;
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
	if (len > info->map->mapX)
		info->map->mapX = len;
	if (!(tmp = malloc(sizeof(char **) * line)))
		return (NULL);	
	i = 0;
	while (i <= line)
	{
		tmp[i] = malloc(sizeof(char *) * info->map->mapX + 1);
		if (i == line)
			ft_memcpy(tmp[i], readed, info->map->mapX + 1);
		else
			ft_memcpy(tmp[i], info->map->map[i], ft_strlen(info->map->map[i]));
		i++;
	}
	free(info->map->map);
	return (tmp);
}

// int		print_map(t_parameters *info, int i)
// {
// 	for (int z = 0; z <= i; z++)
// 	{
// 		for (int j = 0; j <= 15; j++)
// 			printf("%c", info->map->map[z][j]);
// 		printf("\n");
// 	}
// 	return (1);
// }

void	read_infos(int fd, t_parameters *info)
{
	char *readed;
	int i;

	i = 0;
	while (get_next_line(fd, &readed))
	{
		if (readed[0] == 'R')
			define_resolution(info, readed);
		else if (readed[0] == 'N' && readed[1] == 'O' && readed[2] == ' ')
			info->north_texture = read_image_path(readed, info);  // NOT WORKING YET
		else
		{
			if(is_map_line(readed))
			{
				info->map->map = malloc_map(info, readed, i);
				i++;
			}
		}
	}
	info->map->mapY = i;
	info->map->tam_altura = floor(info->height / info->map->mapY);
	info->map->tam_largura = floor(info->width / info->map->mapX);
	info->player = start_player(info);
	info->rays = start_rays(info);
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
	info->map = start_map(info);
}