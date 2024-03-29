/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 09:02:46 by lmartins          #+#    #+#             */
/*   Updated: 2021/08/08 09:54:10 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty_line(char *line)
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

int	end_of_file(int fd, char **line)
{
	while ((get_next_line(fd, line)))
	{
		if (!(is_empty_line(*line)))
			return (FALSE);
	}
	free(*line);
	return (TRUE);
}

int	is_identifier(char *line)
{
	if ((line[0] == 'R' && line[1] == ' ')
		|| (line[0] == 'F' && line[1] == ' ')
		|| (line[0] == 'C' && line[1] == ' ')
		|| (line[0] == 'N' && line[1] == 'O')
		|| (line[0] == 'W' && line[1] == 'E')
		|| (line[0] == 'E' && line[1] == 'A')
		|| (line[0] == 'S' && line[1] == 'O'))
		return (TRUE);
	return (FALSE);
}

int	read_info_if(char *readed, int *fd, int	*i, t_parameters *info)
{
	int		ret;
	int		ismap;

	ismap = FALSE;
	if (readed[0] == ' ' || readed[0] == '1')
	{
		ret = get_map_info(info, readed, i, &ismap);
		if (ret < 0)
			return (ft_error(info, ret));
	}
	else if (is_identifier(readed) && !ismap)
		assign_non_map_info(readed, info);
	else if (!(is_empty_line(readed)) || (ismap && !end_of_file(*fd, &readed)))
		return (ft_error(info, ERROR_INVALID_LINE));
	return (TRUE);
}

void	ft_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
