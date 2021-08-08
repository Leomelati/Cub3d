/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 01:47:39 by lmartins          #+#    #+#             */
/*   Updated: 2021/08/08 08:46:58 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (ft_atoi(string[1]) > x)
			info->width = x;
		else
			info->width = ft_atoi(string[1]);
		if (ft_atoi(string[2]) > y)
			info->height = y;
		else
			info->height = ft_atoi(string[2]);
	}
	if (info->width <= 0 || info->height <= 0)
		ft_error(info, ERROR_SCREEN);
	info->ray = start_rays(info, info->width);
	ft_split_free(string);
}

int	assign_non_map_info(char *line, t_parameters *info)
{
	if (line[0] == 'R' && line[1] == ' ' && info->height == MISS)
		define_resolution(info, line);
	else if (line[0] == 'F' && line[1] == ' ' && info->floor_color == MISS)
		info->floor_color = convert_color(line, info);
	else if (line[0] == 'C' && line[1] == ' ' && info->ceil_color == MISS)
		info->ceil_color = convert_color(line, info);
	else if (line[0] == 'N' && line[1] == 'O' && info->north_tex->img == NULL)
		read_image_path(line, info, info->north_tex, NORTH);
	else if (line[0] == 'S' && line[1] == 'O' && info->south_tex->img == NULL)
		read_image_path(line, info, info->south_tex, SOUTH);
	else if (line[0] == 'W' && line[1] == 'E' && info->west_tex->img == NULL)
		read_image_path(line, info, info->west_tex, WEST);
	else if (line[0] == 'E' && line[1] == 'A' && info->east_tex->img == NULL)
		read_image_path(line, info, info->east_tex, EAST);
	else
	{
		free(line);
		return (ft_error(info, ERROR_INVALID_MAP));
	}
	free(line);
	return (TRUE);
}

int	check_parsed_info(t_parameters *info)
{
	if (!(validate_map(info->map)))
		return (ft_error(info, ERROR_INVALID_MAP));
	else if (!info->map->map_x || !info->map->map_y)
		return (ft_error(info, ERROR_INVALID_MAP));
	else if (!info->width || !info->height
		|| info->width < info->map->map_x || info->height < info->map->map_y)
		return (ft_error(info, ERROR_SCREEN));
	else if (info->ceil_color < 0 || info->floor_color < 0)
		return (ft_error(info, ERROR_COLOR));
	else if (!info->north_tex->img || !info->south_tex->img
		|| !info->east_tex->img || !info->west_tex->img)
		return (ft_error(info, ERROR_PATH));
	else if (info->player->pos_x == MISS || info->player->pos_y == MISS)
		return (ft_error(info, ERROR_PLAYER));
	start_img(info);
	return (TRUE);
}

int	parse_row_map(t_parameters *info, char *line, int row)
{
	int	i;

	info->map->map[row] = line;
	i = -1;
	while (line[++i])
	{
		info->map->map[row][i] = line[i];
		if (!(ft_strchr("NSEW 01", line[i])))
			return (ERROR_CHAR);
		if (ft_strchr("NSEW", line[i]))
			if (parse_initial_position(info, line[i], row, i) < 0)
				return (ERROR_PLAYER);
	}
	return (i);
}

int	read_infos(char *file, t_parameters *info)
{
	char	*readed;
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_error(info, ERROR_ARGC));
	i = 0;
	while (get_next_line(fd, &readed))
	{
		ft_replace(readed, '\t', ' ');
		read_info_if(readed, &fd, &i, info);
	}
	free(readed);
	close(fd);
	return (fill_rolls(info));
}
