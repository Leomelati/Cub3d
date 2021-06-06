/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliar2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 09:02:46 by lmartins          #+#    #+#             */
/*   Updated: 2021/06/06 09:03:20 by lmartins         ###   ########.fr       */
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
