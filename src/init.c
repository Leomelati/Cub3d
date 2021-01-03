/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 22:42:30 by lmartins          #+#    #+#             */
/*   Updated: 2021/01/03 09:30:30 by lmartins         ###   ########.fr       */
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
	player->angle = PI;
	player->pdx = cos(player->angle) * 5;
	player->pdy = sin(player->angle) * 5;
	return (player);
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
	info->player = start_player();
	info->valid = TRUE;
}