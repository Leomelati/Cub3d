/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 01:47:39 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/06 09:04:37 by lmartins         ###   ########.fr       */
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
	info->map->num_rays = info->width / WALL_WIDTH;
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
	else if (line[0] == 'S' && line[1] == ' ' && info->sprite_tex->img == NULL)
		read_image_path(line, info, info->sprite_tex);
	else if (line[0] == 'N' && line[1] == 'O' && info->north_tex->img == NULL)
		read_image_path(line, info, info->north_tex);
	else if (line[0] == 'S' && line[1] == 'O' && info->south_tex->img == NULL)
		read_image_path(line, info, info->south_tex);
	else if (line[0] == 'W' && line[1] == 'E' && info->west_tex->img == NULL)
		read_image_path(line, info, info->west_tex);
	else if (line[0] == 'E' && line[1] == 'A' && info->east_tex->img == NULL)
		read_image_path(line, info, info->east_tex);
	else if (line[0] == 'S' && line[1] == ' ' && info->sprite_tex->img == NULL)
		read_image_path(line, info, info->sprite_tex);
	else
	{
		free(line);
		return (ft_error(info, ERROR_INVALID_MAP));
	}
	free(line);
	return (TRUE);
}

int	is_identifier(char *line)
{
	if ((line[0] == 'R' && line[1] == ' ')
		|| (line[0] == 'F' && line[1] == ' ')
		|| (line[0] == 'C' && line[1] == ' ')
		|| (line[0] == 'S' && line[1] == ' ')
		|| (line[0] == 'N' && line[1] == 'O')
		|| (line[0] == 'W' && line[1] == 'E')
		|| (line[0] == 'E' && line[1] == 'A')
		|| (line[0] == 'S' && line[1] == 'O'))
		return (TRUE);
	return (FALSE);
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
	else if (!info->north_tex || !info->south_tex
		|| !info->east_tex || !info->west_tex || !info->sprite_tex)
		return (ft_error(info, ERROR_PATH));
	else if (info->player->pos_x == MISS || info->player->pos_y == MISS)
		return (ft_error(info, ERROR_PLAYER));
	info->ray = start_rays(info);
	start_img(info);
	//start_sprites(info);
	return (TRUE);
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

t_coordinates	*create_sprite_point(float x, float y)
{
	t_coordinates *point;

	point = ft_calloc(1, sizeof(t_coordinates));
	point->x = x;
	point->y = y;
	return (point);
}

int	parse_row_map(t_parameters *info, char *line, int row)
{
	int	i;

	info->map->map[row] = line;
	i = -1;
	while (line[++i])
	{
		info->map->map[row][i] = line[i];
		if (!(ft_strchr("NSEW 012", line[i])))
			return (ERROR_CHAR);
		if (ft_strchr("NSEW", line[i]))
			if (parse_initial_position(info, line[i], row, i) < 0)
				return (ERROR_PLAYER);
		if (line[i] == '2')
		{
			info->map->sprites_map = (t_coordinates **)allocate_dynamic((void **)info->map->sprites_map, sizeof(t_coordinates *), info->map->num_sprites);
			info->map->sprites_map[info->map->num_sprites] = create_sprite_point(i, row);
			info->map->num_sprites++;
		}
	}
	return (i);
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
	if (!(n_col = parse_row_map(info, line, info->map->map_y)) || n_col < 0)
	{
		free(line);
		return (n_col);
	}
	info->map->map_x = n_col > info->map->map_x ? n_col : info->map->map_x;
	info->map->map_y++;
	i++;
	*row = i;
	return (n_col);
}

int	read_infos(char *file, t_parameters *info)
{
	char	*readed;
	int 	fd;
	int 	ismap;
	int 	ret;
	int		i;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (ft_error(info, ERROR_INVALID_ARGUMENT));
	ismap = FALSE;
	i = 0;
	while (get_next_line(fd, &readed))
	{
		ft_replace(readed, '\t', ' ');
		if (readed[0] == ' ' || readed[0] == '1')
		{
			if ((ret = get_map_info(info, readed, &i, &ismap)) < 0)
				return (ft_error(info, ret));
		}
		else if (is_identifier(readed) && !ismap)
			assign_non_map_info(readed, info);
		else if (!(is_empty_line(readed)) || (ismap && !end_of_file(fd, &readed)))
			return (ft_error(info, ERROR_INVALID_LINE));
	}
	free(readed);
	close(fd);
	return (fill_rolls(info));
}
