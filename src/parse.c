/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 01:47:39 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/07 02:02:05 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_parsed_info(t_parameters *info)
{
	if (info->width == MISS || info->height == MISS)
		define_error_message(ERROR_SCREEN, info);
	if (info->north_texture == NULL || info->south_texture == NULL ||
		info->east_texture == NULL || info->west_texture == NULL)
		define_error_message(ERROR_PATH, info);
	if (info->floor_color == MISS || info->ceilling_color == MISS)
		define_error_message(ERROR_COLOR, info);
}

int		is_map_line(char *readed)
{
	int i;

	i = 0;
	while (readed[i] != '\0')
	{
		if (ft_strchr(VALID_MAP_CHARS, readed[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	define_resolution(t_parameters *info, char *readed)
{
	char	**string;
	int		x;
	int		y;
	int		elements;

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
	if (info->width <= 0 || info->height <= 0)
		define_error_message(ERROR_SCREEN, info);
	free(string);
}

void	read_infos(int fd, t_parameters *info)
{
	char	*readed;
	int		i;

	i = 0;
	while (get_next_line(fd, &readed))
	{
		if (readed[0] == 'R' && readed[1] == ' ')
			define_resolution(info, readed);
		else if (readed[0] == 'F' && readed[1] == ' ')
			info->floor_color = convert_color(readed, info);
		else if (readed[0] == 'C' && readed[1] == ' ')
			info->ceilling_color = convert_color(readed, info);
		else if (readed[0] == 'N' && readed[1] == 'O' && readed[2] == ' ')
			info->north_texture = read_image_path(readed, info);
		else if (readed[0] == 'S' && readed[1] == 'O' && readed[2] == ' ')
			info->south_texture = read_image_path(readed, info);
		else if (readed[0] == 'W' && readed[1] == 'E' && readed[2] == ' ')
			info->west_texture = read_image_path(readed, info);
		else if (readed[0] == 'E' && readed[1] == 'A' && readed[2] == ' ')
			info->east_texture = read_image_path(readed, info);
		else
		{
			if (is_map_line(readed))
			{
				info->map->map = malloc_map(info, readed, i);
				i++;
			}
		}
		free(readed);
	}
	info->map->map_y = i - 1;
	info->map->num_rays = info->width / WALL_WIDTH;
	info->player = start_player(info);
	info->ray = start_rays(info);
	check_parsed_info(info);
}
