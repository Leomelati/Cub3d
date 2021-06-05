/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 01:47:39 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/05 07:22:20 by lmartins         ###   ########.fr       */
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
		info->width = (ft_atoi(string[1]) > x) ? x : ft_atoi(string[1]);
		info->height = (ft_atoi(string[2]) > y) ? y : ft_atoi(string[2]);
	}
	if (info->width <= 0 || info->height <= 0)
		ft_error(info, ERROR_SCREEN);
	info->map->num_rays = info->width / WALL_WIDTH;
	ft_split_free(string);
}

int		is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (*line && line[i] == ' ')
		i++;
	if (line[i] != '\0')
	{
		free(line);
		return (FALSE);
	}
	free(line);
	return (TRUE);
}

int		end_of_file(int fd, char **line)
{
	while ((get_next_line(fd, line)))
	{
		if (!(is_empty_line(*line)))
			return (FALSE);
	}
	free(*line);
	return (TRUE);
}

int		assign_non_map_info(char *readed, t_parameters *info)
{
	if (readed[0] == 'R' && readed[1] == ' ' && (info->width == MISS || info->height == MISS))
			define_resolution(info, readed);
	else if (readed[0] == 'F' && readed[1] == ' ' && info->floor_color == MISS)
		info->floor_color = convert_color(readed, info);
	else if (readed[0] == 'C' && readed[1] == ' ' && info->ceilling_color == MISS)
		info->ceilling_color = convert_color(readed, info);
	else if (readed[0] == 'S' && readed[1] == ' ' && info->sprite_texture->img == NULL)
		read_image_path(readed, info, info->sprite_texture);
	else if (readed[0] == 'N' && readed[1] == 'O' && info->north_texture->img == NULL)
		read_image_path(readed, info, info->north_texture);
	else if (readed[0] == 'S' && readed[1] == 'O' && info->south_texture->img == NULL)
		read_image_path(readed, info, info->south_texture);
	else if (readed[0] == 'W' && readed[1] == 'E' && info->west_texture->img == NULL)
		read_image_path(readed, info, info->west_texture);
	else if (readed[0] == 'E' && readed[1] == 'A' && info->east_texture->img == NULL)
		read_image_path(readed, info, info->east_texture);
	else
	{
		free(readed);
		return (ft_error(info, ERROR_INVALID_MAP));
	}
	free(readed);
	return (TRUE);
}

int			is_identifier(char *line)
{
	if ((line[0] == 'R' && line[1] == ' ') ||
		(line[0] == 'F' && line[1] == ' ') ||
		(line[0] == 'C' && line[1] == ' ') ||
		(line[0] == 'S' && line[1] == ' ') ||
		(line[0] == 'N' && line[1] == 'O') ||
		(line[0] == 'W' && line[1] == 'E') ||
		(line[0] == 'E' && line[1] == 'A') ||
		(line[0] == 'S' && line[1] == 'O'))
		return (TRUE);
	return (FALSE);
}

int	check_char(t_map *map, int i, int j)
{
	if (i > 0 && i < (map->map_y - 1) && j > 0 && j < (map->map_x - 1))
	{
		if (!(ft_strchr("012", map->map[i - 1][j - 1])) ||
			!(ft_strchr("012", map->map[i][j - 1])) ||
			!(ft_strchr("012", map->map[i + 1][j - 1])) ||
			!(ft_strchr("012", map->map[i - 1][j])) ||
			!(ft_strchr("012", map->map[i + 1][j])) ||
			!(ft_strchr("012", map->map[i - 1][j + 1])) ||
			!(ft_strchr("012", map->map[i][j + 1])) ||
			!(ft_strchr("012", map->map[i + 1][j + 1])))
			return (FALSE);
	}
	return (TRUE);
}

int		validate_map(t_map *map)
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

int		check_parsed_info(t_parameters *info)
{
	if (!(validate_map(info->map)))
		return (ft_error(info, ERROR_INVALID_MAP));
	else if (!info->map->map_x || !info->map->map_y)
		return (ft_error(info, ERROR_INVALID_MAP));
	else if (!info->width || !info->height ||
		info->width < info->map->map_x || info->height < info->map->map_y)
		return (ft_error(info, ERROR_SCREEN));
	else if (info->ceilling_color < 0 || info->floor_color < 0)
		return (ft_error(info, ERROR_COLOR));
	else if (!info->north_texture || !info->south_texture ||
		!info->east_texture || !info->west_texture || !info->sprite_texture)
			return (ft_error(info, ERROR_PATH));
	else if (info->player->pos_x == MISS || info->player->pos_y == MISS)
		return (ft_error(info, ERROR_PLAYER));

	// else if (!map->sprite_posit)
		// return (ft_error(map, -14));

	info->ray = start_rays(info);
	start_img(info);
	return (TRUE);
}

int		fill_rolls(t_parameters *info)
{
	int i;
	int j;

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

void	**allocate_dynamic(void **buffer, int size, int m)
{
	void	**new_buffer;
	int		i;

	new_buffer = ft_calloc(m + 2, size);
	i = 0;
	while (i < m)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	if (m > 0)
		free(buffer);
	return (new_buffer);
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

		// if (line[i] == '2')
		// {
		// 	map->sprite_posit = (t_point **)allocate_dynamic(
		// 		(void **)map->sprite_posit, sizeof(t_point *), map->n_sprites);
		// 	map->sprite_posit[map->n_sprites] = create_point(i, row, 0);
		// 	map->n_sprites++;
		// }
	}
	return (i);
}

int			get_map_info(t_parameters *info, char *line, int *row, int *ismap)
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

int		read_infos(char *file, t_parameters *info)
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
