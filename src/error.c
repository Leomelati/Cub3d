/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 02:36:48 by lmartins          #+#    #+#             */
/*   Updated: 2021/03/08 04:41:41 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_extension(char *file, t_parameters *info)
{
	char	*extension;
	int		len;
	int		i;

	len = ft_strlen(file);
	i = len - 4;
	if (i < 4)
		define_error_message(ERROR_EXTENSION, info);
	extension = ft_strdup(&file[i]);
	if (ft_strncmp(extension, ".cub", 5))
		define_error_message(ERROR_EXTENSION, info);
	free(extension);
}

void	define_error_message(int error_code, t_parameters *info)
{
	if (error_code == ERROR_COLOR)
		ft_putendl_fd("Error: Invalid color code.", 1);
	else if (error_code == ERROR_PATH)
		ft_putendl_fd("Error: Invalid texture path.", 1);
	else if (error_code == ERROR_ARGC)
		ft_putendl_fd("Error: Invalid number of arguments.", 1);
	else if (error_code == ERROR_SCREEN)
		ft_putendl_fd("Error: Invalid resolution.", 1);
	else if (error_code == ERROR_PLAYER)
		ft_putendl_fd("Error: Invalid player position.", 1);
	else if (error_code == ERROR_CHAR)
		ft_putendl_fd("Error: Invalid map char.", 1);
	else if (error_code == ERROR_EXTENSION)
		ft_putendl_fd("Error: Invalid file format.", 1);
	destroy_window(info);
}
