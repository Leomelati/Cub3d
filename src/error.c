/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 02:36:48 by lmartins          #+#    #+#             */
/*   Updated: 2021/05/31 08:08:09 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_error(t_parameters *info, int i)
{
	destroy_window(info);
	ft_putendl_fd(define_error_message(i), 1);
	return (close_program());
}

int			ft_arg_error(int i)
{
	ft_putendl_fd(define_error_message(i), 1);
	return (close_program());
}

int			ft_path_error(t_parameters *info)
{
	ft_error(info, ERROR_TEXTURE);
	mlx_destroy_window(info->mlx, info->win);
	return (close_program());
}

void	check_starting_errors(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
		ft_arg_error(ERROR_ARGC);
	else if (argc == 3 && ft_memcmp(argv[2], "--save", 6))
		ft_arg_error(ERROR_INVALID_ARGUMENT);
	check_extension(argv[1]);
}

void	check_extension(char *file)
{
	char	*extension;
	int		len;
	int		i;

	len = ft_strlen(file);
	i = len - 4;
	if (i < 4)
		ft_arg_error(ERROR_EXTENSION);
	extension = ft_strdup(&file[i]);
	if (ft_strncmp(extension, ".cub", 5))
		ft_arg_error(ERROR_EXTENSION);
	free(extension);
}

char 	*define_error_message(int error_code)
{
	if (error_code == ERROR_COLOR)
		return ("Error: Invalid color code.");
	else if (error_code == ERROR_PATH)
		return("Error: Invalid texture path.");
	else if (error_code == ERROR_ARGC)
		return("Error: Invalid number of arguments.");
	else if (error_code == ERROR_SCREEN)
		return("Error: Invalid resolution.");
	else if (error_code == ERROR_PLAYER)
		return("Error: More than one player position or invalid player position.");
	else if (error_code == ERROR_CHAR)
		return("Error: Invalid map char.");
	else if (error_code == ERROR_EXTENSION)
		return("Error: Invalid file format.");
	else if (error_code == ERROR_MLX)
		return("Error: Mlx error.");
	else if (error_code == ERROR_INVALID_ARGUMENT)
		return("Error: Invalid argument.");
	else if (error_code == ERROR_INVALID_LINE)
		return("Error: Invalid line.");
	else if (error_code == ERROR_INVALID_MAP)
		return("Error: Invalid map.");
	else if (error_code == ERROR_INVALID_MAP)
		return("Error: Could not load texture.");
	return (NULL);
}
